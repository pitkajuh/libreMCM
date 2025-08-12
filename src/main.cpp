#include <iostream>
#include <chrono>
#include <getopt.h>
#include <unistd.h>
#include <unordered_set>
#include "File.h"
#include "Equation.h"
#include "FileSettings.h"
#include "FileGraph.h"
#include "FileEquations.h"
#include "NumericalMethod.h"
#include "Vertex.h"

#define GetCurrentDir getcwd

using std::cout;
bool run_deterministic_sim=false;

enum
{
  NUM_METHOD_OPTION,
  TIME_START_OPTION,
  TIME_END_OPTION,
  STEP_SIZE_OPTION
};

static struct option const options[]=
  {
    {"deterministic", 0, 0, 'd'},
    {"num-method", 1, 0, NUM_METHOD_OPTION},
    {"time-start", 1, 0, TIME_START_OPTION},
    {"time-end", 1, 0, TIME_END_OPTION},
    {"step-size", 1, 0, STEP_SIZE_OPTION},
    {0, 0, 0, 0}
  };

void ReadInitialData(const string &directory)
{
  cout<<"Start"<<'\n';
  uint16_t timeStart;
  uint16_t timeEnd;
  uint16_t stepSize;
  FileEquations test3;
  FileGraph test1;
  Vertex *vertices;
  MathOperators operators;
  RungeKutta4 numMethod;
  uint16_t nv;
  Equations equations;
  std::unordered_set<double*> aoea;

#pragma omp taskgroup
  {
#pragma omp task shared(timeStart, timeEnd, stepSize)
    {
      FileSettings test2(directory+"sim_params");
      timeStart=std::stoi(test2.set[test2.settingsNames["time_start"]]);
      if(timeStart<0) throw std::invalid_argument("Starting time cannot be negative");
      timeEnd=std::stoi(test2.set[test2.settingsNames["time_end"]]);
      if(timeEnd<0) throw std::invalid_argument("Ending time cannot be negative");
      stepSize=std::stoi(test2.set[test2.settingsNames["step_size"]]);

      if(timeStart>timeEnd) throw std::invalid_argument("Starting time is larger than ending time");
      if(stepSize==0) throw std::invalid_argument("Step size cannot be zero");
      if(stepSize>=timeEnd) throw std::invalid_argument("Step size is too large.");
      // Get other parameters here before clearing.
      test2.set.clear();
    }
#pragma omp task shared(test3)
    {
      test3.Read(directory+"bin");
    }
#pragma omp task shared(test1)
    {
      test1.Read(directory+"graph.txt");
    }
  }

  test1.Create(timeStart, timeEnd, stepSize);
  numMethod.Create(test1.nx, test1.noOfInitialValue.size());
  nv=test1.all.size();
  vertices=test1.CreateVertices(numMethod.y_np1);

  cout<<"main.cpp "<<test1.N<<" "<<test1.nx<<" "<<test1.ny<<" "<<test1.noOfInitialValue.size()<<'\n';

  std::copy(numMethod.y_np1, numMethod.y_np1+test1.nx, numMethod.y_n);
  std::copy(numMethod.y_np1, numMethod.y_np1+numMethod.nValue, numMethod.valuesSubstitute);


  equations=test3.ParseEquations(test1.vertexNamesMap, operators, numMethod.valuesSubstitute, test1.noOfInitialValue, test1.noOfInitialValue.size());
  cout<<"ok1"<<'\n';
  test1.CreateEdge(test3.equationNames, equations);
  cout<<"ok2"<<'\n';

  numMethod.Calculate(timeStart, timeEnd, stepSize, test1.edgesNew2, test1.N, test1.noOfInitialValue, vertices, nv);
  cout<<"ok3"<<'\n';

  cout<<"Start clearing"<<'\n';

  for(auto &i: equations.equations)
    {
      for(auto &j: i.vertices)
	{
	  if(j.value1!=nullptr)
	    {
	      auto a12=std::find(numMethod.valuesSubstitute, numMethod.valuesSubstitute+numMethod.nValue, *j.value1);

	      if(a12!=j.value1) aoea.insert(j.value1);
	    }

	  if(j.value2!=nullptr)
	    {
	      auto a13=std::find(numMethod.valuesSubstitute, numMethod.valuesSubstitute+numMethod.nValue, *j.value2);

	      if(a13!=j.value2) aoea.insert(j.value2);
	    }

	  if(j.result!=nullptr)
	    {
	      auto a14=std::find(numMethod.valuesSubstitute, numMethod.valuesSubstitute+numMethod.nValue, *j.result);

	      if(a14!=j.result) aoea.insert(j.result);
	    }
	}
    }

  for(auto k: aoea)
    {
      delete k;
    }
  delete [] vertices;
}

int main(int argc, char** argv)
{
  // if(argc<2)
  //   {
  //     cout<<"Provide arguments."<<'\n';
  //     return 0;
  //   }
  // else
  //   {
      // Get current working directory.
      char buff[FILENAME_MAX];
      GetCurrentDir(buff, FILENAME_MAX);
      string directory(buff);
      directory=directory+"/";
      // int c;

      // while((c=getopt_long(argc, argv, "dp", options, NULL))!=-1)
      // 	{
      // 	  switch(c)
      // 	    {
      // 	    case 'd':
      // 	      run_deterministic_sim=true;
      // 	      break;
      // 	    case NUM_METHOD_OPTION:
      // 	      break;
      // 	    case TIME_START_OPTION:
      // 	      break;
      // 	    case TIME_END_OPTION:
      // 	      break;
      // 	    case STEP_SIZE_OPTION:
      // 	      break;
      // 	    default:
      // 	      exit(1);
      // 	    }
      // 	}
      // ReadInitialData(directory);

      // if(run_deterministic_sim)
      // 	{
      // 	  ReadInitialData(directory);
      //

      cout<<"Starting "<<directory<<'\n';
      auto begin=std::chrono::high_resolution_clock::now();
      for(int i=0; i<1; i++)
	{
	  ReadInitialData(directory);
	}
      auto end=std::chrono::high_resolution_clock::now();
      auto duration=std::chrono::duration_cast<std::chrono::microseconds>(end-begin);

      cout<<"Runtime: "<<duration.count()/1000<<" milliseconds "<<(double)duration.count()/1e6<<" seconds"<<'\n';
      cout<<"################################################################"<<'\n';
    // }
  return 0;

}
