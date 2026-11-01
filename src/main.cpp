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
  double timeStart;
  double timeEnd;
  double stepSize;
  FileEquations equationsFromFile;
  FileGraph graphFromFile;
  Vertex *vertices;
  MathOperators operators;
  RungeKutta4 numMethod;
  Equations equations;
  std::unordered_set<double*> memoryToClear;

#pragma omp taskgroup
  {
#pragma omp task shared(timeStart, timeEnd, stepSize)
    {
      FileSettings simulationParameters(directory+"sim_params");
      timeStart=simulationParameters.GetTimeStart();

      if(timeStart<0) throw std::invalid_argument("Starting time cannot be negative");
      timeEnd=simulationParameters.GetTimeEnd();
      if(timeEnd<0) throw std::invalid_argument("Ending time cannot be negative");
      if(timeStart>timeEnd) throw std::invalid_argument("Starting time is larger than ending time");
      stepSize=simulationParameters.GetStepSize();
      if(stepSize==0) throw std::invalid_argument("Step size cannot be zero");
      if(stepSize>=timeEnd) throw std::invalid_argument("Step size is too large.");
      // Get other parameters here before clearing.
      // Get algorithm type, e.g. RK4
      simulationParameters.set.clear();
    }
#pragma omp task shared(equationsFromFile)
    {
      equationsFromFile.Read(directory+"bin");
    }
#pragma omp task shared(graphFromFile)
    {
      graphFromFile.Read(directory+"graph.txt");
    }
  }

  graphFromFile.Create(timeStart, timeEnd, stepSize);
  graphFromFile.InitInitialValues();
  vertices=graphFromFile.CreateVertices(numMethod.y_np1);

  numMethod.Create(graphFromFile.nx, graphFromFile.noOfInitialValue.size());
  std::copy(numMethod.y_np1, numMethod.y_np1+graphFromFile.nx, numMethod.y_n);
  std::copy(numMethod.y_np1, numMethod.y_np1+numMethod.nValue, numMethod.valuesSubstitute);

  equations=equationsFromFile.ParseEquations(graphFromFile.vertexNamesMap, operators, numMethod.valuesSubstitute, graphFromFile.noOfInitialValue);
  graphFromFile.CreateEdge(equationsFromFile.equationNames, equations);

  numMethod.Calculate(timeStart, timeEnd, stepSize, graphFromFile.edgesNew2, graphFromFile.N, graphFromFile.noOfInitialValue, directory);

  cout<<"Start clearing"<<'\n';

  for(auto &i: equations.equations)
    {
      for(auto &j: i.vertices)
	{
	  if(j.value1!=nullptr)
	    {
	      auto a12=std::find(numMethod.valuesSubstitute, numMethod.valuesSubstitute+numMethod.nValue, *j.value1);

	      if(a12!=j.value1) memoryToClear.insert(j.value1);
	    }

	  if(j.value2!=nullptr)
	    {
	      auto a13=std::find(numMethod.valuesSubstitute, numMethod.valuesSubstitute+numMethod.nValue, *j.value2);

	      if(a13!=j.value2) memoryToClear.insert(j.value2);
	    }

	  if(j.result!=nullptr)
	    {
	      auto a14=std::find(numMethod.valuesSubstitute, numMethod.valuesSubstitute+numMethod.nValue, *j.result);

	      if(a14!=j.result) memoryToClear.insert(j.result);
	    }
	}
    }

  for(auto k: memoryToClear)
    {
      delete k;
    }
  delete [] vertices;
}

int main(int argc, char** argv)
{
  if(argc>2)
    {
      cout<<"Too many arguments."<<'\n';
      return 0;
    }
  else
    {
      // Get current working directory.
      char buff[FILENAME_MAX];
      GetCurrentDir(buff, FILENAME_MAX);
      string directory(buff);
      directory=directory+"/"+argv[1];

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
    }
  return 0;

}
