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
#include <iostream>
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
#include "../util/is_string_numerical_value.h"
#include "../util/string_split.h"

using std::to_string;
using std::fstream;
using std::ios_base;
using std::ios;
using std::cout;

const string ERROR="Error, ";
const string NOT_DEFINED=" was not defined in";
const string FILE_STR=" file.";

void sim_param_error(const bool param_found, const bool is_numerical, const string var)
{
  if(not param_found)
    {
      throw std::domain_error(ERROR+var+NOT_DEFINED+SIM_PARAMS+FILE_STR);
    }
  else if(not is_numerical)
    {
      throw std::invalid_argument(ERROR+"value of "+var+" is invalid in "+SIM_PARAMS+FILE_STR);
    }
}

void are_sim_params_defined(const bool param_found, const string param_name, const string value)
{
  const bool is_numerical=is_string_numerical_value(value);

  if(param_name==TIME_START)
    {
      sim_param_error(param_found, is_numerical, TIME_START);
    }
  else if(param_name==TIME_END)
    {
      sim_param_error(param_found, is_numerical, TIME_END);
    }
  else if(param_name==STEP_SIZE)
    {
      sim_param_error(param_found, is_numerical, STEP_SIZE);
    }
  else if(param_name==NUM_METHOD)
    {
      // Check whether numerical method was defined in config file.
      if(param_found)
	{
	  // Check if the defined numerical method was valid.
	  const bool num_method_defined=is_in_vector(available_num_methods, value);

	  if(num_method_defined)
	    {
	      num_method=value;
	    }
	  else
	    {
	      cout<<"Numerical method "<<NUM_METHOD<<" is not valid. Using default setting (rk4)."<<'\n';
	      num_method=RK4; // Temporary. At the moment only one numerical method is defined. Will be removed when there are more.
	    }
	}
      else
	{
	  cout<<"Numerical method (num_method) was not defined, using default setting (rk4)."<<'\n';
	  num_method=RK4; // Temporary. At the moment only one numerical method is defined. Will be removed when there are more.
	}
    }
}

void read_sim_params(const string directory)
{
  bool no_num_method=false;
  bool sim_settings_found=false;
  bool time_start_found=false;
  bool time_end_found=false;
  bool step_size_found=false;
  bool line_empty;
  const string FILE_NAME=directory+SIM_PARAMS;
  const string SIM_BRACKET=SIMULATION_SETTINGS+CURLY_BRACKET_O;
  string line;
  string name;
  string line_commented;
  string value;
  string t_start_str;
  string t_end_str;
  string step_size_str;
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

	  if(name==TIME_START)
	    {
	      t_start_str=value;
	      time_start_found=true;
	    }
	  else if(name==TIME_END)
	    {
	      t_end_str=value;
	      time_end_found=true;
	    }
	  else if(name==STEP_SIZE)
	    {
	      step_size_str=value;
	      step_size_found=true;
	    }
	  else if(name==NUM_METHOD)
	    {
	      num_method=value;
	      no_num_method=true;
	    }
	}
    }
  are_sim_params_defined(sim_settings_found, SIMULATION_SETTINGS, value);
  are_sim_params_defined(time_start_found, TIME_START, t_start_str);
  t_start=stod(t_start_str);
  are_sim_params_defined(time_end_found, TIME_END, t_end_str);
  t_end=stod(t_end_str);
  are_sim_params_defined(step_size_found, STEP_SIZE, step_size_str);
  step_size=stod(step_size_str);
  are_sim_params_defined(no_num_method, NUM_METHOD, num_method);
}
