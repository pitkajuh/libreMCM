/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <algorithm>
#include <fstream>
#include "../class/AllCompartmentInitialValuesHalfLife.h"
#include "../class/AllInitialValuesHalfLife.h"
#include "../class/CompartmentAllInitialValuesHalfLife.h"
#include "../class/SplittedString.h"
#include "../global/all_parameters.h"
#include "../global/all_values.h"
#include "../global/global_constants.h"
#include "../global/initial_value_map.h"
#include "../global/compartment_parameters.h"
#include "../util/remove_white_space.h"
#include "../util/is_commented.h"

using std::find;
using std::fstream;
using std::ios_base;
using std::ios;

void parse_initial_value(CompartmentAllInitialValuesHalfLife compartment_parameters_i)
{
  int i=0;
  int j=0;
  int initial_value_size;
  const string name=compartment_parameters_i.compartment;
  AllInitialValuesHalfLife initial_values=compartment_parameters_i.initial_values;
  const int size=initial_values.size()-1;
  InitialValuesHalfLife initial_value;
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

  if(find(all_parameters.begin(), all_parameters.end(), parameter_name)==all_parameters.end())
    {
      all_parameters.push_back(parameter_name);
    }
}

InitialValuesHalfLife read_compartment_element(const string elem, const string compartment_name)
{
  int i=0;
  const int size=elem.size()-1;
  float half_life;
  string empty;
  string name;
  string fchar;
  string value;
  InitialValueHalfLife result;
  InitialValuesHalfLife rt;
  SplittedString compartment_initial_value;

  while(i<=size)
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
	  empty+=fchar;
	}
      i++;
    }
  return rt;
}

void read_compartment_def(const string directory)
{
  int size;
  bool compartments_found=false;
  bool compartment_name_found=false;
  bool initial_values_found=false;
  bool compartments_saved=false;
  bool line_is_empty;
  bool commented_or_not;
  const string compartments_str="compartments";
  const string initial_values="initial_values";
  const string file_name=directory+compartments_str;
  const string compartments_bracket=compartments_str+CURLY_BRACKET_O;
  const string initial_values_bracket=initial_values+CURLY_BRACKET_O;
  string line;
  string first_char;
  string compartment_name;
  string compartment_c;
  string line_commented;
  string line_substr;
  InitialValuesHalfLife compartment_i;
  AllInitialValuesHalfLife compartments_values;
  CompartmentAllInitialValuesHalfLife compartment_parameters_i;
  fstream bin_loaded(file_name, ios_base::in | ios::binary);

  while(getline(bin_loaded, line))
    {
      line=remove_white_space(line);
      commented_or_not=is_commented(line);
      line_is_empty=line.empty();

      if(line_is_empty or commented_or_not)
	{
	  continue;
	}
      else if(not compartments_saved)
	{
	  if(bin_loaded.eof())
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
	      size=line.size()-1;
	      first_char=line[size];
	      line_substr=line.substr(0, size);

	      if(first_char==CURLY_BRACKET_O and line_substr!=initial_values)
		{
		  size=line.size()-1;
		  compartment_name=line.substr(0, size);
		  compartment_name_found=true;
		}
	      else if(compartment_name_found)
		{
		  if(line==initial_values or line==initial_values_bracket)
		    {
		      initial_values_found=true;
		    }
		  else if(initial_values_found and line!=CURLY_BRACKET_C)
		    {
		      compartment_i=read_compartment_element(line, compartment_name);
		      compartments_values.push_back(compartment_i);
		    }
		  else if(initial_values_found and line==CURLY_BRACKET_C)
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
  bin_loaded.close();
}
