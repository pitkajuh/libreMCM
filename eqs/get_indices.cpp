/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../global/compartment_indice_data.h"
#include "../global/constant_indice_data.h"
#include "../global/global_constants.h"
#include "../math/is_constant.h"
#include "../math/is_variable.h"
#include "../math/calculate_equation_constants.h"
#include "../util/is_string_numerical_value.h"

void get_indices(vector<string> equation_total)
{
  // This function finds indices which contain constant or variable (compartment).
  int i=0;
  const int size=equation_total.size()-1;
  bool constant_check;
  bool compartment_check;
  bool numerical_value_check;
  string fchar;
  vector<int> constant_indices;
  vector<int> compartment_indices;
  vector<string> constant_names;
  vector<string> compartment_names;
  IndicesData constant_locations;
  IndicesData compartment_locations;

  while(i<=size)
    {
      fchar=equation_total[i];
      constant_check=is_constant(fchar);
      compartment_check=is_variable(fchar);

      if(constant_check)
	{
	  constant_names.push_back(fchar);
	  constant_indices.push_back(i);
	}
      else if(compartment_check)
	{
	  compartment_names.push_back(fchar);
	  compartment_indices.push_back(i);
	}
      i++;
    }

  constant_locations.names=constant_names;
  constant_locations.indices=constant_indices;
  constant_indice_data.push_back(constant_locations);

  compartment_locations.names=compartment_names;
  compartment_locations.indices=compartment_indices;
  compartment_indice_data.push_back(compartment_locations);
}
