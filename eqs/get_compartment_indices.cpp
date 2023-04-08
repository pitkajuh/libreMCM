/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../global/compartment_indice_data_upd.h"
#include "../global/global_constants.h"
#include "../math/is_variable.h"
#include "../math/calculate_equation_constants.h"

void get_compartment_indices(vector<string> equation_total)
{
  // This function finds indices which contain variable (compartment).
  int i=0;
  const int size=equation_total.size()-1;
  bool compartment_check;
  string fchar;
  vector<string> compartment_names;
  vector<int> compartment_indices;
  IndicesData compartment_locations;

  while(i<=size)
    {
      fchar=equation_total[i];
      compartment_check=is_variable(fchar);

      if(compartment_check)
	{
	  compartment_names.push_back(fchar);
	  compartment_indices.push_back(i);
	}
      i++;
    }
  compartment_locations.names=compartment_names;
  compartment_locations.indices=compartment_indices;
  compartment_indice_data_upd.push_back(compartment_locations);
}
