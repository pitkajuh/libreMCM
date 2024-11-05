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
#include "inc/namespace.h"
#include "rcfg/get_bin.h"
#include "util/MapUtils.h"
#include "util/CreateInitialValues.h"
#include "util/ParseInitialValues.h"
#include "comp/GetCompartment.h"
#include "eqs/EquationAddSubtract.h"
#include "eqs/ParseEquations.h"
#include "eqs/CreateEquationTemplates.h"

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
  ifstream bin(directory+"bin");
  streampos *f=new streampos;
  *f=0;
  const SMap constants_map=GetMap(bin, f);
  const SMap equations_map=GetMap(bin, f);
  bin.close();
  delete f;

  ifstream sim(directory+"sim_params");
  const SMap test=GetMap(sim);
  sim.close();

  ifstream compartments(directory+"compartments");
  Map<string, InitialValues> ivs=GetInitialValues(compartments);
  compartments.close();

  ifstream compartment(directory+"compartment.csv");
  Csv csv=GetCompartment(compartment);
  csv.GetDiagonal();
  compartment.close();

  const vector<string> iv_names=CreateAllInitialValues(ivs);
  const Map<string, DInitialValues> ivs_s=ParseInitialValues(ivs, iv_names);
  const Map<string, AddSubtract> add_subtract=EquationAddSubtract(csv);
  const Map<string, Equation*> equationMap=ParseEquations(equations_map, csv.diagonal);
  CreateEquationTemplates(equationMap, constants_map);
}

int main(int argc, char** argv)
{
  if(argc<2)
    {
      cout<<"Provide arguments."<<'\n';
      return 0;
    }
  else
    {
      // Get current working directory.
      char buff[FILENAME_MAX];
      GetCurrentDir(buff, FILENAME_MAX);
      string directory(buff);
      directory=directory+"/";
      int c;

      while((c=getopt_long(argc, argv, "dp", options, NULL))!=-1)
	{
	  switch(c)
	    {
	    case 'd':
	      run_deterministic_sim=true;
	      break;
	    case NUM_METHOD_OPTION:
	      break;
	    case TIME_START_OPTION:
	      break;
	    case TIME_END_OPTION:
	      break;
	    case STEP_SIZE_OPTION:
	      break;
	    default:
	      exit(1);
	    }
	}

      auto begin=std::chrono::high_resolution_clock::now();
      cout<<"Starting "<<directory<<'\n';

      if(run_deterministic_sim)
	{
	  ReadInitialData(directory);
	}

      auto end=std::chrono::high_resolution_clock::now();
      auto duration=std::chrono::duration_cast<std::chrono::microseconds>(end-begin);

      cout<<"Runtime: "<<duration.count()<<" microseconds "<<(double)duration.count()/1000<<" milliseconds"<<'\n';
      cout<<"################################################################"<<'\n';
    }
  return 0;

}
