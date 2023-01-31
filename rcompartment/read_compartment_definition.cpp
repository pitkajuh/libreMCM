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
#include <fstream>
#include <vector>
#include "../global/global.h"
#include "../rcfg/read_config_sub.h"

using namespace std;

vector<string> compartments;
vector<tuple<string, vector<vector<tuple<string, string, int>>>>> compartment_parameters_rt;
const string compartments_str="compartments";
vector<tuple<string, // compartment_name
	     vector<
	       vector<
		 tuple<
		   string, // parameter name
		   string, // parameter value
		   int // parameter half-life, is zero if parameter is not a radionuclide
		   >>
	       >
	     >
       > compartment_parameters;

vector<tuple<string, string, int>> read_compartment_element(string elem, string compartment_name)
{
  int i=0;
  const string empty_str="";
  string empty=empty_str;
  string fchar;
  string name=empty_str;
  string value;
  vector<tuple<string, string, int>> rt;
  int half_life;
  tuple<string, string, int> result_tuple;

  while(i<=elem.size()-1)
    {
      fchar=elem[i];

      if(fchar==equal_sign)
	{
	  name=compartment_name+parm_delim+empty;
	  empty=empty_str;
	}
      else if(fchar==delimiter)
	{
	  value=empty;
	  // get half life if is radionuclide
	  result_tuple=make_tuple(name, value, half_life);
	  rt.push_back(result_tuple);
	  empty=empty_str;
	}
      else
	{
	  empty=empty+fchar;
	}
      i++;
    }

  return rt;
}

void read_compartment_def(string directory)
{
  const string file_name=directory+"compartments";
  const string radionuclides="radionuclides";
  const string materials="content";
  fstream bin_loaded(file_name, ios_base::in | ios::binary);
  string line;
  string line_a;
  string first_char;
  string compartment_name;
  bool compartments_found=false;
  bool compartments_saved=false;
  bool compartment_name_found=false;
  bool materials_found=false;
  vector<vector<tuple<string, string, int>>> compartments_values;
  string line_commented;
  string line_substr;
  vector<tuple<string, string, int>> element_read;

  tuple<string, // compartment_name
	     vector<
	       vector<
		 tuple<
		   string, // parameter name
		   string, // parameter value
		   int // parameter half-life, is zero if parameter is not a radionuclide
		   >>
	       >
	     >
       compartment_parameters_i;

  while(getline(bin_loaded, line))
    {
      line_commented=line_commented_or_not(line);

      if(line.empty() or line_commented.empty())
	{
	  continue;
	}
      else if(!compartments_saved)
	{
	  if(line==curly_bracket_c and compartments_found)
	    {
	      compartments_saved=true;
	      continue;
	    }
	  else if(line==compartments_str or line==compartments_str+curly_bracket_o)
	    {
	      compartments_found=true;
	      continue;
	    }
	  else if(compartments_found)
	    {
	      line_a=remove_white_space(line);
	      first_char=line_a[line_a.size()-1];
	      line_substr=line_a.substr(0, line_a.size()-1);

	      if(first_char==curly_bracket_o and line_substr!=materials)
		{
		  compartment_name=line_a.substr(0, line_a.size()-1);
		  compartment_name_found=true;
		}
	      else if(compartment_name_found)
		{
		  if(line_a==materials or line_a==materials+curly_bracket_o)
		    {
		      materials_found=true;
		    }
		  else if(materials_found and line_a!=curly_bracket_c)
		    {
		      compartments_values.push_back(read_compartment_element(line_a, compartment_name));
		    }
		  else if(line_a==curly_bracket_c)
		    {
		      compartment_parameters_i=make_tuple(compartment_name, compartments_values);
		      compartment_parameters.push_back(compartment_parameters_i);
		      compartments_values.clear();
		      compartment_name_found=false;
		      materials_found=false;
		    }
		}
	    }
	}
    }

  compartment_parameters_rt=compartment_parameters;
}

void get_compartment_parameters(string directory)
{
  read_compartment_def(directory);
}

tuple<string, string> get_compartment_parameter_value_subroutine(string parameter_wanted)
{
  int i=0;
  const string empty_str="";
  string fchar;
  string empty=empty_str;
  string compartment_name;
  tuple<string, string> rt;

  while(i<=parameter_wanted.size()-1)
    {
      fchar=parameter_wanted[i];

      if(fchar==parm_delim)
	{
	  compartment_name=empty;
	  empty=empty_str;
	}
      else
	{
	  empty=empty+fchar;
	}
      i++;
    }

  rt=make_tuple(compartment_name, empty);
  return rt;
}

string get_compartment_parameter_value(string parameter_wanted)
{
  int i=0;
  int j=0;
  int k=0;
  string compartment_name;
  vector<vector<tuple<string, string, int>>> parameters;
  vector<tuple<string, string, int>> parameters2;
  tuple<string, string, int> parameter;
  string rt=not_found;
  bool found=false;
  tuple<string, string> wanted_compartment_and_parameter=get_compartment_parameter_value_subroutine(parameter_wanted);
  string compartment_name_wanted=get<0>(wanted_compartment_and_parameter);
  string parameter_name_wanted=get<1>(wanted_compartment_and_parameter);
  tuple<string, vector<vector<tuple<string, string, int>>>> compartment_parameters_rt_i;
  tuple<string, string, int> parameters2_k;
  string parameter_search;

  while(i<=compartment_parameters_rt.size()-1)
    {
      compartment_parameters_rt_i=compartment_parameters_rt[i];
      compartment_name=get<0>(compartment_parameters_rt_i);
      parameters=get<1>(compartment_parameters_rt_i);

      if(compartment_name==compartment_name_wanted)
	{
	  while(j<=parameters.size()-1)
	    {
	      parameters2=parameters[j];

	      if(found)
		{
		  break;
		}
	      while(k<=parameters2.size()-1)
		{
		  parameters2_k=parameters2[k];
		  parameter_search=get<0>(parameters2_k);

		  if(found)
		    {
		      break;
		    }
		  else if(parameter_search==parameter_wanted)
		    {
		      rt=get<1>(parameters2_k);
		      found=true;
		      break;
		    }
		  k++;
		}
	      k=0;
	      j++;
	    }
	}
      j=0;
      i++;
    }

  return rt;
}
