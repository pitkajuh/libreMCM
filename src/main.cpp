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
#include <climits>
#include "global/t_start.h"
#include "global/t_end.h"
#include "global/step_size.h"
#include "global/num_method.h"
#include "bin/run_deterministic.h"
#include "rcfg/get_sim_params.h"
#include "rcfg/get_bin.h"
#include "eqs/replace_indices.h"
#include "rcompartment/get_compartment.h"
#include "rcompartment/get_compartment_parameters.h"
#include "rcompartment/get_compartment_equations.h"
#include "map/create_initial_value_map.h"
#include "map/create_compartment_target_map.h"
#include "map/create_compartment_maps.h"
#include "eqs/parse_compartment_equations.h"
#include "util/valid_value_check.h"
#include "wdata/parse_initial_values.h"

#define GetCurrentDir getcwd

using std::cout;

bool run_deterministic_sim=false;

enum
{
  NUM_METHOD_OPTION=CHAR_MAX+1,
  TIME_START_OPTION,
  TIME_END_OPTION,
  STEP_SIZE_OPTION
};

static struct option const long_options[]=
  {
    {"deterministic", 0, 0, 'd'},
    {"num-method", 1, 0, NUM_METHOD_OPTION},
    {"time-start", 1, 0, TIME_START_OPTION},
    {"time-end", 1, 0, TIME_END_OPTION},
    {"step-size", 1, 0, STEP_SIZE_OPTION},
    {0, 0, 0, 0}
  };

void get_and_parse_data(const string directory)
{
  get_bin(directory);
  get_sim_params(directory);
  get_compartment(directory);
  get_compartment_parameters(directory);

  get_compartment_equations();
  create_target_compartment_map();
  create_initial_value_map();
  parse_initial_values();
  create_compartment_map();
  parse_compartment_equations();
  replace_indices();
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

      while((c=getopt_long(argc, argv, "dp", long_options, NULL))!=-1)
	{
	  switch(c)
	    {
	    case 'd':
	      cout<<"d"<<'\n';
	      run_deterministic_sim=true;
	      break;
	    case NUM_METHOD_OPTION:
	      cout<<"NUM_METHOD_OPTION "<<'\n';
	      num_method=optarg;
	      // num_method_valid(num_method);
	      num_method_found=true;
	      break;
	    case TIME_START_OPTION:
	      cout<<"TIME_START_OPTION "<<optarg<<'\n';
	      t_start=value_check(optarg);
	      time_start_found=true;
	      break;
	    case TIME_END_OPTION:
	      cout<<"TIME_END_OPTION"<<'\n';
	      t_end=value_check(optarg);
	      time_end_found=true;
	      break;
	    case STEP_SIZE_OPTION:
	      cout<<"STEP_SIZE_OPTION"<<'\n';
	      step_size=value_check(optarg);
	      step_size_found=true;
	      break;
	    // default:
	    //   exit(1);
	    }
	}

      auto begin=std::chrono::high_resolution_clock::now();
      cout<<"Starting "<<directory<<'\n';

      if(run_deterministic_sim)
	{
	  get_and_parse_data(directory);
	  run_deterministic(directory);
	}
      auto end=std::chrono::high_resolution_clock::now();
      auto duration=std::chrono::duration_cast<std::chrono::microseconds>(end-begin);
      cout<<"Runtime: "<<duration.count()<<" microseconds "<<(double)duration.count()/1000<<" milliseconds"<<'\n';
      cout<<"################################################################"<<'\n';
    }
  return 0;
}
