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
  FileSettings test2(directory+"sim_params");
  const uint16_t timeStart=std::stoi(test2.set[test2.settingsNames["time_start"]]);
  const uint16_t timeEnd=std::stoi(test2.set[test2.settingsNames["time_end"]]);
  const uint16_t stepSize=std::stoi(test2.set[test2.settingsNames["step_size"]]);

  if(timeStart>timeEnd) throw std::invalid_argument("Starting time is larger than ending time");
  if(stepSize>=timeEnd) throw std::invalid_argument("Step size is too large.");

  // Get other parameters here before clearing.
  test2.set.clear();

  FileEquations test3(directory+"bin");

  FileGraph test1(directory+"graph.txt", timeStart, timeEnd, stepSize);

  uint16_t a1=test1.nx/test1.noOfInitialValue.size();
  if(a1<test1.noOfInitialValue.size()) a1=test1.noOfInitialValue.size();

  // RungeKutta4 numMethod(test1.nx, test1.noOfInitialValue.size());
  RungeKutta4 numMethod(test1.nx, a1);

  // double *y_np1=nullptr;
  test1.InitResults(numMethod.y_np1);

  MathOperators operators;

  cout<<"main.cpp "<<test1.N<<" "<<test1.nx<<" "<<test1.ny<<" "<<test1.noOfInitialValue.size()<<'\n';

  std::copy(numMethod.y_np1, numMethod.y_np1+test1.nx, numMethod.y_n);
  // std::copy(numMethod.y_np1, numMethod.y_np1+numMethod.nx/numMethod.nValue, numMethod.valuesSubstitute);
  std::copy(numMethod.y_np1, numMethod.y_np1+numMethod.nValue, numMethod.valuesSubstitute);
  cout<<numMethod.nx/numMethod.nValue<<" "<<numMethod.nValue<<" "<<std::min(1, 2)<<'\n';

  // for(int i=0; i<numMethod.nx/numMethod.nValue; i++)
  // for(int i=0; i<std::min(numMethod.nValue, a1); i++)
  cout<<"a1 "<<a1<<'\n';
  // if(a1<numMethod.nValue) a1=numMethod.nValue;

  // for(int i=0; i<numMethod.nValue; i++)
  for(int i=0; i<a1; i++)
    {
      cout<<"I="<<i<<" "<<&numMethod.valuesSubstitute[i]<<" "<<numMethod.valuesSubstitute[i]<<'\n';
    }
  cout<<"ok"<<'\n';
  std::unordered_set<double*> aoea;

  Equations equations=test3.ParseEquations(test1.vertexNamesMap, operators, numMethod.valuesSubstitute, test1.noOfInitialValue, test1.noOfInitialValue.size());

  test1.CreateEdge(test3.equationNames, equations);

  numMethod.Calculate(timeStart, timeEnd, stepSize, test1.edgesNew2, equations, test1.N, test1.noOfInitialValue);


  // equations.Calculate();

  cout<<"Start clearing"<<'\n';
  // int k=0;
  for(auto &i: equations.equations)
    {
      for(auto &j: i.vertices)
	{
	  // cout<<k<<'\n';
	  if(j.value1!=nullptr)
	    {
	      // auto a12=std::find(numMethod.y_n, numMethod.y_n+test1.nx, *j.value1);
	      auto a12=std::find(numMethod.valuesSubstitute, numMethod.valuesSubstitute+numMethod.nValue, *j.value1);

	      if(a12!=j.value1)
		{
		  // cout<<"a12!=j.value1; "<<j.value1<<" "<<*j.value1<<'\n';
		  aoea.insert(j.value1);
		  // delete j.value1;
		}
	    }

	  if(j.value2!=nullptr)
	    {
	      // auto a13=std::find(numMethod.y_n, numMethod.y_n+test1.nx, *j.value2);
	      auto a13=std::find(numMethod.valuesSubstitute, numMethod.valuesSubstitute+numMethod.nValue, *j.value2);

	      if(a13!=j.value2)
		{
		  // cout<<"a13!=j.value2 "<<j.value2<<" "<<*j.value2<<'\n';
		  aoea.insert(j.value2);
		  // delete j.value2;
		}
	    }

	  if(j.result!=nullptr)
	    {
	      // auto a14=std::find(numMethod.y_n, numMethod.y_n+test1.nx, *j.result);
	      auto a14=std::find(numMethod.valuesSubstitute, numMethod.valuesSubstitute+numMethod.nValue, *j.result);

	      if(a14!=j.result)
		{
		  // cout<<"a14!=j.result "<<j.result<<" "<<*j.result<<'\n';
		  aoea.insert(j.result);
		  // delete j.result;
		}
	    }
	  // k++;
	  // cout<<" "<<'\n';
	}


    }

  // delete [] y_np1;
  // delete numMethod;

  for(auto k: aoea)
    {
      // cout<<"k="<<k<<'\n';
      delete k;
    }
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
