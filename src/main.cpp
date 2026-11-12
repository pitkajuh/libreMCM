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
#include "Graph.h"

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
  Graph graph;
  FileEquations equationsFromFile;
  FileGraph graphFromFile;
  FileSettings simulationParameters;
  MathOperators operators;
  RungeKutta4 numMethod;
  Equations equations;
  std::unordered_set<double*> memoryToClear;

#pragma omp taskgroup
  {
#pragma omp task shared(simulationParameters)
    {
      simulationParameters.Read(directory+"sim_params");
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

  graphFromFile.CreateGraph(simulationParameters);
  graphFromFile.CreateVertices(graph, numMethod.y_np1);
  numMethod.Create(graphFromFile.nx, graphFromFile.noOfInitialValue.size());

  graph.PrintGraph();

  std::copy(numMethod.y_np1.begin(), numMethod.y_np1.begin()+graphFromFile.nx, numMethod.y_n.begin());
  std::copy(numMethod.y_np1.begin(), numMethod.y_np1.begin()+numMethod.nValue, numMethod.valuesSubstitute.begin());

  equations=equationsFromFile.ParseEquations(graph, operators, numMethod.valuesSubstitute, graphFromFile.noOfInitialValue);
  graphFromFile.CreateEdge(graph, equationsFromFile.equationNames, equations);

  numMethod.Calculate(simulationParameters, graph, graphFromFile.N, directory);

  cout<<"Start clearing"<<'\n';

  for(auto &i: equations.equations)
    {
      for(auto &j: i.vertices)
	{
	  if(j.value1!=nullptr)
	    {
	      auto a12=std::find(numMethod.valuesSubstitute.begin(), numMethod.valuesSubstitute.begin()+numMethod.nValue, *j.value1);

	      if(&*a12!=&*j.value1) memoryToClear.insert(j.value1);
	    }

	  if(j.value2!=nullptr)
	    {
	      auto a13=std::find(numMethod.valuesSubstitute.begin(), numMethod.valuesSubstitute.begin()+numMethod.nValue, *j.value2);

	      if(&*a13!=&*j.value2) memoryToClear.insert(j.value2);
	    }

	  if(j.result!=nullptr)
	    {
	      auto a14=std::find(numMethod.valuesSubstitute.begin(), numMethod.valuesSubstitute.begin()+numMethod.nValue, *j.result);

	      if(&*a14!=&*j.result) memoryToClear.insert(j.result);
	    }
	}
    }

  for(auto k: memoryToClear)
    {
      delete k;
    }

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
