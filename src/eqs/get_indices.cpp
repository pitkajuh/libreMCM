/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../global/constants_map.h"
#include "../global/compartment_indice_data.h"
#include "../global/constant_indice_data.h"
#include "../global/global_constants.h"
#include "../math/is_constant.h"
#include "../math/is_variable.h"
#include "../math/calculate_equation_constants.h"
#include "../util/vector_convert.h"

const bool vec_check_variable(const vector<string> vec)
{
  bool result=false;

  for(const auto&i: vec)
    {
      result=is_variable(i);

      if(result){break;}
    }
  return result;
}

const bool vec_check_constant(const vector<string> vec)
{
  bool result=false;

  for(const auto&i: vec)
    {
      result=is_constant(i);

      if(result){break;}
    }
  return result;
}

void get_indices(const vector<string> equation_total)
{
  // This function finds indices which contain constant or variable (compartment).
  int i=0;
  const int size=equation_total.size()-1;
  bool constant_check;
  bool compartment_check;
  string fchar;
  vector<int> constant_indices;
  vector<int> compartment_indices;
  vector<string> constant_names;
  vector<string> compartment_names;
  vector<string> index_vector;
  IndicesData constant_locations;
  IndicesData compartment_locations;

  while(i<=size)
    {
      fchar=equation_total[i];
      index_vector=equation_string_to_equation_vector(fchar);
      constant_check=vec_check_constant(index_vector);
      compartment_check=vec_check_variable(index_vector);

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
