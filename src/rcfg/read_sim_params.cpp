/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <stdexcept>
#include <fstream>
#include "../global/global_constants.h"
#include "../global/sim_params_constants.h"
#include "../global/t_start.h"
#include "../global/t_end.h"
#include "../global/step_size.h"
#include "../global/num_method.h"
#include "../global/num_methods.h"
#include "../util/line_remove_comment.h"
#include "../util/remove_white_space.h"
#include "../util/is_in_vector.h"
#include "../util/string_split.h"
#include "../util/valid_value_check.h"

#include <iostream>
using std::cout;

using std::to_string;
using std::fstream;
using std::ios_base;
using std::ios;

void settings_defined(const bool found)
{
  if(not found)
    {
      throw std::domain_error("Error, simulation settings were not found.");
    }
}

void num_method_valid(const string value)
{
  // Check if the defined numerical method was valid.
  const bool num_method_defined=is_in_vector(available_num_methods, value);

  if(num_method_defined)
    {
      num_method=value;
    }
  else
    {
      cout<<"Numerical method (num_method) was not defined, using default setting (rk4)."<<'\n';
      num_method=RK4; // Temporary. At the moment only one numerical method is defined. Will be removed when there are more.
    }
}

void read_sim_params(const string directory)
{
  bool sim_settings_found=false;
  bool probabilistic_found=false;
  bool iterations_found=false;
  bool line_empty;
  const string FILE_NAME=directory+SIM_PARAMS;
  const string SIM_BRACKET=SIMULATION_SETTINGS+CURLY_BRACKET_O;
  string line;
  string name;
  string line_commented;
  string value;
  fstream sim_params_loaded(FILE_NAME, ios_base::in | ios::binary);
  SplittedString splitted;

  while(getline(sim_params_loaded, line))
    {
      line=remove_white_space(line);
      line_commented=line_remove_comment(line);
      line_empty=line.empty();

      if(line_empty)
	{
	  continue;
	}
      else if(line==SIMULATION_SETTINGS or line==SIM_BRACKET)
	{
	  sim_settings_found=true;
	}
      else if(sim_settings_found and line==CURLY_BRACKET_C)
	{
	  break;
	}
      else if(sim_settings_found)
	{
	  splitted=string_split(line, EQUAL_SIGN);
	  name=splitted.splitted_string_part1;
	  value=splitted.splitted_string_part2;

	  if(name==TIME_START and not time_start_found)
	    {
	      t_start=value_check(value);
	      time_start_found=true;
	    }
	  else if(name==TIME_END and not time_end_found)
	    {
	      t_end=value_check(value);
	      time_end_found=true;
	    }
	  else if(name==STEP_SIZE and not step_size_found)
	    {
	      step_size=value_check(value);
	      step_size_found=true;
	    }
	  else if(name==NUM_METHOD and not num_method_found)
	    {
	      num_method=value;
	      num_method_valid(num_method);
	      num_method_found=true;
	    }
	}
    }
  sim_params_loaded.close();
  settings_defined(sim_settings_found);
}
