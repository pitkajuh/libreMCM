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
#include "global.h"
#include "read_config_sub.h"

using namespace std;

int t_start, t_end, steps;

string get_sim_param_name(string str)
{
  int i=0;
  string empty="", fchar;
  bool eq_found=false;

  while(i<=str.size()-1)
    {
      fchar=str[i];
      if(fchar=="=")
	{
	  break;
	}
      else
	{
	  empty=empty+str[i];
	}
      i++;
    }
  return empty;
}

string get_sim_param_value(string str)
{
  int i=0;
  string empty="", fchar;
  bool eq_found=false;

  while(i<=str.size()-1)
    {
      fchar=str[i];
      if(fchar=="=")
	{
	  eq_found=true;
	}
      else if(eq_found)
	{
	  empty=empty+str[i];
	}
      i++;
    }
  return empty;
}

void read_sim_params()
{
  fstream sim_params_loaded("cfg/sim_params", ios_base::in | ios::binary);
  string line, name;
  bool sim_settings_found=false;

  while(getline(sim_params_loaded, line))
    {
      line=remove_white_space(line);

      if(line.empty())
	{
	  continue;
	}
      else if(line_commented_or_not(line).empty())
	{
	  continue;
	}
      else if(line=="simulation_settings"+curly_bracket_o)
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
	  if(name=="time_start")
	    {
	      t_start=stod(get_sim_param_value(line));
	    }
	  else if(name=="time_end")
	    {
	      t_end=stod(get_sim_param_value(line));
	    }
	  else if(name=="steps")
	    {
	      steps=stod(get_sim_param_value(line));
	    }
	}
    }
}

void get_sim_params()
{
  read_sim_params();
}
