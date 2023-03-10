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
#include "../util/string_split.h"
#include "../wdata/values_to_graph.h"
#include "../map/create_maps.h"

string get_compartment_parameter_value(string parameter_wanted)
{
  SplittedString splitted_string=split_string_in_two(parameter_wanted, parm_delim);
  string compartment=splitted_string.splitted_string_part1;
  string parameter=splitted_string.splitted_string_part2;

  map<string, vector<string>> parameter_map1=compartment_map[compartment];
  vector<string> param_value=parameter_map1[parameter];
  int size=param_value.size();
  string rt=param_value[size-1];

  return rt;
}
