/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <iostream>
#include <chrono>
#include <getopt.h>
#include <unistd.h>
#include "namespace.h"
#include "File.h"
#include "GraphEquation.h"
#include "FileSettings.h"
#include "FileGraph.h"
#include "FileEquations.h"

#define GetCurrentDir getcwd

using std::cout;
using namespace libremcm;
using InitialValues=SMap;
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
  const unsigned timeStart=std::stoi(test2.set["time_start"]);
  const unsigned timeEnd=std::stoi(test2.set["time_end"]);
  const unsigned stepSize=std::stoi(test2.set["step_size"]);
  // Get other parameters here before clearing.
  test2.set.clear();

  FileGraph test1(directory+"graph.txt", timeStart, timeEnd, stepSize);
  double *results=nullptr;
  test1.InitResults(results, timeStart);


  FileEquations test3(directory+"bin");
  map<string, GraphEquation*> eqs=test3.ParseEquations(test1.vertexNames);
  // map<string, GraphEquation*> eqs=ParseEquations(test3.equations2, test1.vertexNames);



  for(auto &[name, equation]: eqs)
    {
      cout<<name<<" "<<equation<<'\n';
      // equation->SubstituteConstants(constants_map);
      delete equation;
    }


  delete [] results;
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
      for(int i=0; i<1000; i++)
	{
	  ReadInitialData(directory);
	}
      auto end=std::chrono::high_resolution_clock::now();
      auto duration=std::chrono::duration_cast<std::chrono::microseconds>(end-begin);

      cout<<"Runtime: "<<duration.count()/1000<<" milliseconds "<<(double)duration.count()/1e6<<" milliseconds"<<'\n';
      cout<<"################################################################"<<'\n';
    // }
  return 0;

}
