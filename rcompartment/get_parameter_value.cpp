/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../global/global.h"
#include "../wdata/values_to_graph.h"
#include "../map/create_maps.h"
#include "../map/initial_value_map.h"

string get_compartment_parameter_value(const string parameter_wanted)
{
  SplittedString splitted_string=initial_value_map[parameter_wanted];
  string compartment=splitted_string.splitted_string_part1;
  string parameter=splitted_string.splitted_string_part2;
  map<string, vector<string>> parameter_map1=compartment_map[compartment];
  vector<string> param_value=parameter_map1[parameter];
  int size=param_value.size();
  string rt=param_value[size-1];

  return rt;
}
