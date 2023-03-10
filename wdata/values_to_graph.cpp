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
#include <map>
#include <algorithm>
#include "../class/CompartmentInitialValuesHalfLife.h"
#include "../class/AllInitialValues.h"
#include "../global/global.h"
#include "../rcompartment/read_compartment.h"
#include "../rcompartment/get_compartment_equations.h"
#include "../map/create_maps.h"
#include "../eqs/parse_compartment_equations.h"
#include "../util/string_split.h"
#include "../util/is_in_vector.h"

using std::map;
using std::cout;
using std::endl;

vector<string> all_parameters;
vector<string> all_compartments;
AllInitialValues initial_values_all;

void add_to_all_parameters(string parameter_name)
{
  // Adds parameter to all_parameters vector, if it has not already been added.
  int i=0;
  string parameter;
  bool found=false;

  if(all_parameters.size()>0)
    {
      while(i<=all_parameters.size()-1)
	{
	  parameter=all_parameters[i];

	  if(parameter==parameter_name)
	    {
	      found=true;
	      break;
	    }

	  i++;
	}
    }
  if(!found)
    {
      all_parameters.push_back(parameter_name);
    }
}

void add_all_values()
{
  int i=0;
  int j=0;
  int k=0;
  int size=all_values.get_size();
  int params_size;
  int values_size;
  string param_name;
  string param_value;
  string param_name_splitted_1;
  string compartment_name;
  SplittedString param_name_splitted;
  CompartmentAllInitialValuesHalfLife val;
  AllInitialValuesHalfLife params;
  InitialValuesHalfLife params_j;
  InitialValueHalfLife params_k;
  InitialValue initial_value;
  InitialValues initial_values;

  while(i<=size-1)
    {
      val=all_values.get(i);
      compartment_name=val.compartment;
      params=val.initial_values;
      all_compartments.push_back(compartment_name);
      params_size=params.get_size();

      while(j<=params_size-1)
	{
	  params_j=params.get(j);
	  values_size=params_j.get_size();

	  while(k<=values_size-1)
	    {
	      params_k=params_j.get(k);
	      param_name=params_k.initial_value_name;
	      param_name_splitted=split_string_in_two(param_name, parm_delim);
	      param_name_splitted_1=param_name_splitted.splitted_string_part2;
	      param_value=params_k.initial_value;

	      initial_value.initial_value_name=param_name_splitted_1;
	      initial_value.initial_value=param_value;
	      initial_values.push_back(initial_value);
	      add_to_all_parameters(param_name_splitted_1);
	      k++;
	    }
	  k=0;
	  j++;
	}
      j=0;
      i++;
      initial_values_all.push_back(initial_values);
      initial_values.clear();
    }
  create_compartment_map();
}
