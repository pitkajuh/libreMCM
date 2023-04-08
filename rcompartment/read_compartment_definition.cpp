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
#include "../global/all_parameters.h"
#include "../global/all_values.h"
#include "../class/AllCompartmentInitialValuesHalfLife.h"
#include "../class/AllInitialValuesHalfLife.h"
#include "../class/CompartmentAllInitialValuesHalfLife.h"
#include "../class/SplittedString.h"
#include "../global/global_constants.h"
#include "../util/remove_white_space.h"
#include "../util/line_remove_comment.h"
#include "../global/initial_value_map.h"
#include "../global/compartment_parameters.h"

#include <iostream>
using std::fstream;
using std::ios_base;
using std::ios;

void parse_initial_value(CompartmentAllInitialValuesHalfLife compartment_parameters_i)
{
  int i=0;
  int j=0;
  const string name=compartment_parameters_i.compartment;
  AllInitialValuesHalfLife initial_values=compartment_parameters_i.initial_values;
  const int size=initial_values.size()-1;
  InitialValuesHalfLife initial_value;
  int initial_value_size;
  InitialValueHalfLife initial_value_i;
  InitialValuesHalfLife values;
  CompartmentAllInitialValuesHalfLife add_values_i;
  AllInitialValuesHalfLife values_ii;
  vector<InitialValuesHalfLife> values_i;

  while(i<=size)
    {
      initial_value=initial_values[i];
      initial_value_size=initial_value.size()-1;

      while(j<=initial_value_size)
	{
	  initial_value_i=initial_value[j];
	  values.push_back(initial_value_i);
	  j++;
	}
      j=0;
      i++;
    }

  add_values_i.compartment=name;
  values_i.push_back(values);
  values_ii.initial_values=values_i;
  add_values_i.initial_values=values_ii;
  all_values.push_back(add_values_i);
}

void add_to_all_parameters(const string parameter_name)
{
  // Adds parameter to all_parameters vector, if it has not already been added.
  const int size=all_parameters.size();
  bool found=false;

  if(size>0)
    {
      for(const auto&i: all_parameters)
	{
	  if(i==parameter_name)
	    {
	      found=true;
	      break;
	    }
	}
    }
  if(!found)
    {
      all_parameters.push_back(parameter_name);
    }
}

InitialValuesHalfLife read_compartment_element(const string elem, const string compartment_name)
{
  int i=0;
  const int size=elem.size();
  float half_life;
  string empty;
  string name;
  string fchar;
  string value;
  InitialValueHalfLife result;
  InitialValuesHalfLife rt;
  SplittedString compartment_initial_value;

  while(i<=size-1)
    {
      fchar=elem[i];

      if(fchar==EQUAL_SIGN)
	{
	  name=compartment_name+PARM_DELIM+empty;
	  compartment_initial_value.splitted_string_part1=compartment_name;
	  compartment_initial_value.splitted_string_part2=empty;
	  add_to_all_parameters(empty);
	  initial_value_map[name]=compartment_initial_value;
	  empty="";
	}
      else if(fchar==DELIMITER)
	{
	  value=empty;
	  // Get half life
	  result.initial_value_name=name;
	  result.initial_value=value;
	  result.half_life=half_life;
	  rt.push_back(result);
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

void read_compartment_def(const string directory)
{
  const string compartments_str="compartments";
  const string file_name=directory+compartments_str;
  const string initial_values="initial_values";
  const string compartments_bracket=compartments_str+CURLY_BRACKET_O;
  const string initial_values_bracket=initial_values+CURLY_BRACKET_O;
  string line;
  string line_a;
  string first_char;
  string compartment_name;
  string compartment_c;
  string line_commented;
  string line_substr;
  int size_a;
  bool compartments_found=false;
  bool compartments_saved=false;
  bool compartment_name_found=false;
  bool initial_values_found=false;
  bool line_is_empty;
  bool line_commented_is_empty;
  InitialValuesHalfLife compartment_i;
  AllInitialValuesHalfLife compartments_values;
  CompartmentAllInitialValuesHalfLife compartment_parameters_i;
  fstream bin_loaded(file_name, ios_base::in | ios::binary);

  while(getline(bin_loaded, line))
    {
      line_commented=line_remove_comment(line);
      line_is_empty=line.empty();
      line_commented_is_empty=line_commented.empty();

      if(line_is_empty or line_commented_is_empty)
	{
	  continue;
	}
      else if(!compartments_saved)
	{
	  if(line==CURLY_BRACKET_C and compartments_found)
	    {
	      compartments_saved=true;
	      continue;
	    }
	  else if(line==compartments_str or line==compartments_bracket)
	    {
	      compartments_found=true;
	      continue;
	    }
	  else if(compartments_found)
	    {
	      line_a=remove_white_space(line);
	      size_a=line_a.size()-1;
	      first_char=line_a[size_a];
	      line_substr=line_a.substr(0, size_a);

	      if(first_char==CURLY_BRACKET_O and line_substr!=initial_values)
		{
		  size_a=line_a.size()-1;
		  compartment_name=line_a.substr(0, size_a);
		  compartment_name_found=true;
		}
	      else if(compartment_name_found)
		{
		  if(line_a==initial_values or line_a==initial_values_bracket)
		    {
		      initial_values_found=true;
		    }
		  else if(initial_values_found and line_a!=CURLY_BRACKET_C)
		    {
		      compartment_i=read_compartment_element(line_a, compartment_name);
		      compartments_values.push_back(compartment_i);
		    }
		  else if(line_a==CURLY_BRACKET_C)
		    {
		      compartment_parameters_i.compartment=compartment_name;
		      compartment_parameters_i.initial_values=compartments_values;

		      parse_initial_value(compartment_parameters_i);
		      compartment_parameters.push_back(compartment_parameters_i);

		      compartments_values.clear();
		      compartment_name_found=false;
		      initial_values_found=false;
		    }
		}
	    }
	}
    }
}
