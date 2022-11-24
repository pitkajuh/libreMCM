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
#include "global.h"
#include "read_config_sub.h"

using namespace std;

vector<string> compartments;
string compartments_str="compartments";
vector<tuple<string, vector<vector<tuple<string, string, int>>>>> compartment_parameters;

vector<tuple<string, string, int>> read_compartment_element(string elem, string compartment_name)
{
  int i=0;
  string empty="", fchar, name="", value;
  vector<tuple<string, string, int>> rt;
  int half_life=0;

  while(i<=elem.size()-1)
    {
      fchar=elem[i];

      if(fchar=="=")
	{
	  name=compartment_name+"@"+empty;
	  empty="";
	}
      else if(fchar==delimiter)
	{
	  value=empty;
	  // get half life if is radionuclide
	  rt.push_back(make_tuple(name, value, half_life));
	  empty="";
	}
      else
	{
	  empty=empty+fchar;
	}
      i++;
    }
  return rt;
}

void test_pr(vector<vector<tuple<string, string, int>>> compartment_values)
{
  int i=0, j=0;
  vector<tuple<string, string, int>> jj;
  tuple<string, string, int> dd;

  while(i<=compartment_values.size()-1)
    {
      while(j<=compartment_values[i].size()-1)
	{
	  jj=compartment_values[i];
	  j++;
	}
      j=0;
      i++;
    }
}

vector<tuple<string, vector<vector<tuple<string, string, int>>>>> read_compartment_def()
{
  fstream bin_loaded("cfg/compartments", ios_base::in | ios::binary);
  string line, line_a, radionuclides="radionuclides", materials="content", first_char, compartment_name;
  bool compartments_found=false, compartments_saved=false, compartment_name_found=false, materials_found=false;
  vector<vector<tuple<string, string, int>>> compartments_values;

  while(getline(bin_loaded, line))
    {
      if(line.empty())
	{
	  continue;
	}
      else if(line_commented_or_not(line).empty())
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
	      if(first_char==curly_bracket_o and line_a.substr(0, line_a.size()-1)!=materials)
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
		      compartment_parameters.push_back(make_tuple(compartment_name, compartments_values));
		      compartments_values.clear();
		      compartment_name_found=false;
		      materials_found=false;
		    }
		}
	    }
	}
    }

  return compartment_parameters;
}

vector<tuple<string, vector<vector<tuple<string, string, int>>>>> get_compartment_parameters()
{
  return read_compartment_def();
}

vector<tuple<string, vector<vector<tuple<string, string, int>>>>> compartment_parameters_rt=get_compartment_parameters();

tuple<string, string> get_compartment_parameter_value_subroutine(string parameter_wanted)
{
  int i=0;
  string fchar, empty="", compartment_name;

  while(i<=parameter_wanted.size()-1)
    {
      fchar=parameter_wanted[i];
      if(fchar=="@")
	{
	  compartment_name=empty;
	  empty="";
	}
      else
	{
	  empty=empty+fchar;
	}
      i++;
    }

  return make_tuple(compartment_name, empty);
}

string get_compartment_parameter_value(string parameter_wanted)
{
  int i=0, j=0, k=0;
  string compartment_name;
  vector<vector<tuple<string, string, int>>> parameters;
  vector<tuple<string, string, int>> parameters2;
  tuple<string, string, int> parameter;
  string rt="Not found";
  bool found=false;

  tuple<string, string>  wanted_compartment_and_parameter=get_compartment_parameter_value_subroutine(parameter_wanted);
  string compartment_name_wanted=get<0>(wanted_compartment_and_parameter);
  string parameter_name_wanted=get<1>(wanted_compartment_and_parameter);

  while(i<=compartment_parameters_rt.size()-1)
    {
      compartment_name=get<0>(compartment_parameters_rt[i]);
      parameters=get<1>(compartment_parameters_rt[i]);

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
		  if(found)
		    {
		      break;
		    }
		  else if(get<0>(parameters2[k])==parameter_wanted)
		    {
		      rt=get<1>(parameters2[k]);
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
