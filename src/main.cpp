/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <string>
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
using std::string;
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

void ReadInitialData(const string directory)
{
  ifstream bin(directory+"bin");
  streampos *f=new streampos;
  *f=0;
  SMap constants_map=GetMap(bin, f);
  cout<<" "<<'\n';
  SMap equations_map=GetMap(bin, f);
  bin.close();
  delete f;

  cout<<" "<<'\n';
  ifstream sim(directory+"sim_params");
  SMap test=GetMap(sim);
  sim.close();

  cout<<" "<<'\n';

  ifstream compartments(directory+"compartments");
  Map<string, InitialValues> ivs=GetInitialValues(compartments);
  compartments.close();

  ifstream compartment(directory+"compartment.csv");
  Csv csv=GetCompartment(compartment);
  csv.GetDiagonal();
  compartment.close();

  Map<string, AddSubtract> add_subtract=EquationAddSubtract(csv);
  Map<string, MathOperations> equations_map2=ParseEquations(equations_map);
  CreateEquationTemplates(equations_map2, csv, constants_map);

  vector<string> iv_names=CreateAllInitialValues(ivs);
  Map<string, DInitialValues> ivs_s=ParseInitialValues(ivs, iv_names);


//   get_sim_params(directory);
//   get_compartment(directory);
//   get_compartment_parameters(directory);

//   get_compartment_equations();
//   create_target_compartment_Map();
//   create_initial_value_Map();
//   parse_initial_values();
//   create_compartment_Map();
//   parse_compartment_equations();
//   replace_indices();
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
	      // solver_valid(optarg);
	      // num_method_found=true;
	      break;
	    case TIME_START_OPTION:
	      // t_start=value_check(optarg);
	      // time_start_found=true;
	      break;
	    case TIME_END_OPTION:
	      // t_end=value_check(optarg);
	      // time_end_found=true;
	      break;
	    case STEP_SIZE_OPTION:
	      // step_size=value_check(optarg);
	      // step_size_found=true;
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
	  // run_deterministic(directory);
	}

      auto end=std::chrono::high_resolution_clock::now();
      auto duration=std::chrono::duration_cast<std::chrono::microseconds>(end-begin);

      cout<<"Runtime: "<<duration.count()<<" microseconds "<<(double)duration.count()/1000<<" milliseconds"<<'\n';
      cout<<"################################################################"<<'\n';
    }
  return 0;

}
