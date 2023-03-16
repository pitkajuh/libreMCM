/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <fstream>
#include "read_constants.h"
#include "../global/global.h"
#include "../util/line_remove_comment.h"
#include "../util/remove_white_space.h"

using std::fstream;
using std::ios_base;
using std::ios;

double t_start;
double t_end;
double step_size;

string get_sim_param_name(const string str)
{
  int i=0;
  const int size=str.size();
  string empty="";
  string fchar;
  bool eq_found=false;

  while(i<=size-1)
    {
      fchar=str[i];

      if(fchar==EQUAL_SIGN)
	{
	  break;
	}
      else
	{
	  empty=empty+fchar;
	}
      i++;
    }
  return empty;
}

string get_sim_param_value(const string str)
{
  int i=0;
  const int size=str.size();
  string empty="";
  string fchar;
  bool eq_found=false;

  while(i<=size-1)
    {
      fchar=str[i];

      if(fchar==EQUAL_SIGN)
	{
	  eq_found=true;
	}
      else if(eq_found)
	{
	  empty=empty+fchar;
	}
      i++;
    }
  return empty;
}

void read_sim_params(const string directory)
{
  const string file_name=directory+"sim_params";
  const string simulation_settings="simulation_settings";
  const string time_start="time_start";
  const string time_end="time_end";
  const string step_size_str="step_size";
  string line;
  string name;
  string t_start_str;
  string t_end_str;
  string step_size_str1;
  string line_commented;
  bool sim_settings_found=false;
  bool line_empty;
  bool commented_line_empty;
  fstream sim_params_loaded(file_name, ios_base::in | ios::binary);

  while(getline(sim_params_loaded, line))
    {
      line=remove_white_space(line);
      line_commented=line_remove_comment(line);
      line_empty=line.empty();
      commented_line_empty=line_commented.empty();

      if(line_empty or commented_line_empty)
	{
	  continue;
	}
      else if(line==simulation_settings+CURLY_BRACKET_O)
	{
	  sim_settings_found=true;
	}
      else if(sim_settings_found and line==CURLY_BRACKET_C)
	{
	  break;
	}
      else if(sim_settings_found)
	{
	  name=get_sim_param_name(line);

	  if(name==time_start)
	    {
	      t_start_str=get_sim_param_value(line);
	      t_start=stod(t_start_str);
	    }
	  else if(name==time_end)
	    {
	      t_end_str=get_sim_param_value(line);
	      t_end=stod(t_end_str);
	    }
	  else if(name==step_size_str)
	    {
	      step_size_str1=get_sim_param_value(line);
	      step_size=stod(step_size_str1);
	    }
	}
    }
}
