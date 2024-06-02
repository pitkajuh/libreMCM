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
#include "rcfg/get_bin.h"
#include "util/MapUtils.h"
#include "comp/GetCompartment.h"
#include "eqs/EquationAddSubtract.h"

#define GetCurrentDir getcwd

using std::cout;
using std::string;
using InitialValues=unordered_map<string, string>;
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
  streampos *from=new streampos;
  *from=0;
  const unordered_map<string, string> constants_map=GetBin(bin, from);
  cout<<" "<<'\n';
  const unordered_map<string, string> equations_map=GetBin(bin, from);
  cout<<" "<<'\n';
  bin.close();
  delete from;

  ifstream sim(directory+"sim_params");
  from=new streampos;
  *from=0;
  const unordered_map<string, string> settings_map=GetBin(sim, from);
  cout<<" "<<'\n';
  sim.close();
  delete from;

  ifstream compartments(directory+"compartments");
  from=new streampos;
  *from=0;
  unordered_map<string, InitialValues> iv=GetInitialValues(compartments, from);
  compartments.close();
  delete from;

   ifstream compartment(directory+"compartment.csv");
   Csv csv=GetCompartment(compartment);
   csv.GetDiagonal();
   compartment.close();

   unordered_map<string, AddSubtract> add_subtract=EquationAddSubtract(csv);

  // GetBin(directory);
  // cout<<" "<<'\n';
  // GetSettings(directory);
  // cout<<" "<<'\n';
  // GetInitialValues(directory);
  // // cout<<" "<<'\n';




//   get_sim_params(directory);
//   get_compartment(directory);
//   get_compartment_parameters(directory);

//   get_compartment_equations();
//   create_target_compartment_map();
//   create_initial_value_map();
//   parse_initial_values();
//   create_compartment_map();
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
