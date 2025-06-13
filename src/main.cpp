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
  NumericalMethod *numMethod=new RungeKutta4(test1.N);
  // NumericalMethod *numMethod=new RungeKutta4(test1.nx);
  std::copy(results, results+test1.N, numMethod->currentValues);
  // std::copy(results, results+test1.nx, numMethod->currentValues);


  // for(int i=0; i<test1.nx; i++)
  //   {
  //     // cout<<"i="<<i<<" "<<&numMethod->currentValues[i]<<" "<<&results[i]<<'\n';
  //     numMethod->currentValues[i]=results[i];
  //   }

  test3.ParseEquations(test1.vertexNamesMap, operators, numMethod->currentValues, test1.noOfInitialValue);

  // double *a=new double[2];
  // a[0]=1;
  // a[1]=2;

  // double *a1=new double[2];
  // a1[0]=a[0];
  // a1[1]=a[1];

  // double *b1=new double;
  // double *b2=new double;
  // b1=&a1[0];
  // b2=&a1[1];
  // delete b1;
  // cout<<&a[0]<<" "<<b1<<'\n';
  // delete [] a;
  // delete [] a1;
  // // delete b1;
  // delete b2;


  vector<double*> aoea;

  for(auto &i: test3.vertices)
    {
      for(auto &j: i)
	{
	  // auto aa=find(variableValue.begin(), variableValue.end(), *j.value1)==variableValue.end();
	  // cout<<aa<<'\n';
	  // if(find(variableValue.begin(), variableValue.begin(), j.value1)==variableValue.end()) cout<<"AA"<<'\n';;

	  if(find(aoea.begin(), aoea.end(), j.value1)==aoea.end()) aoea.emplace_back(j.value1);
	  if(find(aoea.begin(), aoea.end(), j.value2)==aoea.end()) aoea.emplace_back(j.value2);
	  if(find(aoea.begin(), aoea.end(), j.result)==aoea.end()) aoea.emplace_back(j.result);

	  // if(find(aoea.begin(), aoea.end(), j.value1)==aoea.end()) aoea.emplace_back(j.value1);
	  // if(find(aoea.begin(), aoea.end(), j.value2)==aoea.end()) aoea.emplace_back(j.value2);
	  // if(find(aoea.begin(), aoea.end(), j.result)==aoea.end()) aoea.emplace_back(j.result);
	}
    }

  // delete [] results;
  // delete numMethod;

  for(auto k: aoea)
    {
      cout<<k<<'\n';
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
