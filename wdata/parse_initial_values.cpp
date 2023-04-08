/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../global/initial_values_all.h"
#include "../class/AllInitialValues.h"
#include "../global/all_values.h"
#include "../global/initial_value_map.h"
#include "../util/is_in_vector.h"

void parse_initial_values()
{
  int i=0;
  int j=0;
  int k=0;
  const int size=all_values.size()-1;
  int params_size;
  int values_size;
  string param_name;
  string param_value;
  string param_name_splitted_1;
  string compartment_name;
  SplittedString param_name_splitted;
  SplittedString param_name_splitted1;
  CompartmentAllInitialValuesHalfLife val;
  AllInitialValuesHalfLife params;
  InitialValuesHalfLife params_j;
  InitialValueHalfLife params_k;
  InitialValues initial_values;
  InitialValue initial_value;

  while(i<=size)
    {
      val=all_values[i];
      compartment_name=val.compartment;
      params=val.initial_values;
      params_size=params.size()-1;

      while(j<=params_size)
	{
	  params_j=params[j];
	  values_size=params_j.size()-1;

	  while(k<=values_size)
	    {
	      params_k=params_j[k];
	      param_name=params_k.initial_value_name;
	      param_name_splitted=initial_value_map[param_name];

	      param_name_splitted_1=param_name_splitted.splitted_string_part2;
	      param_value=params_k.initial_value;

	      initial_value.initial_value_name=param_name_splitted_1;
	      initial_value.initial_value=param_value;
	      initial_values.push_back(initial_value);
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
}
