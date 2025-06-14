#include <iostream>
#include <chrono>
#include <getopt.h>
#include <unistd.h>
#include "File.h"
#include "GraphEquation.h"
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
  FileSettings test2(directory+"sim_params");
  const uint16_t timeStart=std::stoi(test2.set[test2.settingsNames["time_start"]]);
  const uint16_t timeEnd=std::stoi(test2.set[test2.settingsNames["time_end"]]);
  const uint16_t stepSize=std::stoi(test2.set[test2.settingsNames["step_size"]]);

  // Get other parameters here before clearing.
  test2.set.clear();

  FileEquations test3(directory+"bin");

  FileGraph test1(directory+"graph.txt", timeStart, timeEnd, stepSize);
  double *results=nullptr;
  test1.InitResults(results);

  MathOperators operators;

  cout<<test1.N<<" "<<test1.nx<<" "<<test1.ny<<'\n';
  NumericalMethod *numMethod=new RungeKutta4(test1.nx);
  // NumericalMethod *numMethod=new RungeKutta4(test1.nx);
  std::copy(results, results+test1.nx, numMethod->currentValues);
  // std::copy(results, results+test1.nx, numMethod->currentValues);

  vector<double*> aoea;

  for(int i=0; i<test1.nx; i++)
    {
      cout<<"i="<<i<<" "<<&numMethod->currentValues[i]<<" "<<&results[i]<<" "<<numMethod->currentValues[i]<<" "<<results[i]<<'\n';
      // aoea.emplace_back(&numMethod->currentValues[i]);
      // numMethod->currentValues[i]=results[i];
    }

  test3.ParseEquations(test1.vertexNamesMap, operators, numMethod->currentValues, test1.noOfInitialValue);

  for(auto &i: test3.vertices)
    {
      for(auto &j: i)
	{
	  // auto aa=find(variableValue.begin(), variableValue.end(), *j.value1)==variableValue.end();
	  // cout<<aa<<'\n';
	  // if(find(variableValue.begin(), variableValue.begin(), j.value1)==variableValue.end()) cout<<"AA"<<'\n';;



	  //-----------------------------

	  auto b=numMethod->currentValues;
	  auto b1=b+test1.nx;

	  auto a12=std::find(b, b1, *j.value1);
	  cout<<"a12 "<<a12<<'\n';
	  // auto a122=find(aoea.begin(), aoea.end(), j.value1)==aoea.end();
	  // auto a1222=find(aoea.begin(), aoea.end(), a12)!=aoea.end();

	  cout<<a12<<" "<<j.value1<<'\n';

	  if(a12!=j.value1)
	    {
	      cout<<"aoea.emplace_back(j.value1);"<<'\n';
	      aoea.emplace_back(j.value1);
	    }

	  // if(a122 and a1222)
	  //   {
	  //     cout<<"find(aoea.begin(), aoea.end(), j.value1)==aoea.end() and find(aoea.begin(), aoea.end(), a12)!=aoea.end()"<<'\n';
	  //     cout<<"Add "<<j.value1<<" "<<*j.value1<<'\n';
	  //     aoea.emplace_back(j.value1);
	  //   }

	  auto a13=std::find(b, b1, *j.value2);
	  cout<<"a13 "<<a13<<'\n';
	  // auto a133=find(aoea.begin(), aoea.end(), j.value2)==aoea.end();
	  // auto a1333=find(aoea.begin(), aoea.end(), a13)!=aoea.end();

	  cout<<a13<<" "<<j.value2<<'\n';

	  if(a13!=j.value2)
	    {
	      cout<<"a13!=j.value1"<<'\n';
	      aoea.emplace_back(j.value2);
	    }

	  // if(a133 and a1333)
	  //   {
	  //     cout<<"find(aoea.begin(), aoea.end(), j.value2)==aoea.end() and find(aoea.begin(), aoea.end(), a13)!=aoea.end()"<<'\n';
	  //     cout<<"Add13 "<<j.value1<<" "<<*j.value1<<'\n';
	  //     aoea.emplace_back(j.value2);
	  //   }


	  if(j.result!=nullptr)
	    {
	      auto a14=std::find(b, b1, *j.result);
	      cout<<"a14 "<<a14<<'\n';
	      // auto a15=find(aoea.begin(), aoea.end(), j.result)==aoea.end();
	      // auto a16=find(aoea.begin(), aoea.end(), a14)!=aoea.end();
	      if(a14!=j.result) aoea.emplace_back(j.result);
	    }


	  // if(a15 and a16)
	  //   {
	  //     cout<<"find(aoea.begin(), aoea.end(), j.result)==aoea.end() and find(aoea.begin(), aoea.end(), a14)!=aoea.end()"<<'\n';
	  //     cout<<"result add "<<'\n';
	  //     aoea.emplace_back(j.result);
	  //   }

	  //-----------------------------

	  // if(find(aoea.begin(), aoea.end(), j.value1)==aoea.end()) aoea.emplace_back(j.value1);
	  // if(find(aoea.begin(), aoea.end(), j.value2)==aoea.end()) aoea.emplace_back(j.value2);
	  // if(find(aoea.begin(), aoea.end(), j.result)==aoea.end()) aoea.emplace_back(j.result);

	  // if(find(aoea.begin(), aoea.end(), j.value1)==aoea.end()) aoea.emplace_back(j.value1);
	  // if(find(aoea.begin(), aoea.end(), j.value2)==aoea.end()) aoea.emplace_back(j.value2);
	  // if(find(aoea.begin(), aoea.end(), j.result)==aoea.end()) aoea.emplace_back(j.result);
	}
    }

  delete [] results;
  delete numMethod;
  cout<<"SIZE "<<aoea.size()<<'\n';
  for(auto k: aoea)
    {
      cout<<"k="<<k<<'\n';
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
