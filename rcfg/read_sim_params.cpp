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

int t_start;
int t_end;
int steps;

string get_sim_param_name(string str)
{
  int i=0;
  int size=str.size();
  string empty="";
  string fchar;
  bool eq_found=false;

  while(i<=size-1)
    {
      fchar=str[i];

      if(fchar==equal_sign)
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

string get_sim_param_value(string str)
{
  int i=0;
  int size=str.size();
  string empty="";
  string fchar;
  bool eq_found=false;

  while(i<=size-1)
    {
      fchar=str[i];

      if(fchar==equal_sign)
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

void read_sim_params(string directory)
{
  const string file_name=directory+"sim_params";
  const string simulation_settings="simulation_settings";
  const string time_start="time_start";
  const string time_end="time_end";
  const string steps_str="step_size";
  string line;
  string name;
  string t_start_str;
  string t_end_str;
  string steps_str1;
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
      else if(line==simulation_settings+curly_bracket_o)
	{
	  sim_settings_found=true;
	}
      else if(sim_settings_found and line==curly_bracket_c)
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
	  else if(name==steps_str)
	    {
	      steps_str1=get_sim_param_value(line);
	      steps=stod(steps_str1);
	    }
	}
    }
}
