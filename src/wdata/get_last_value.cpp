/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../global/global_constants.h"
#include "../global/compartment_map.h"
#include "../class/SplittedString.h"

string get_last_value(const SplittedString param)
{
  string compartment_name_wanted=param.splitted_string_part1;
  const string parameter_name_wanted=param.splitted_string_part2;
  map<string, vector<string>> vec_map;
  vector<string> vec;
  int size;
  string value_wanted;
  string parameter_value;

  vec_map=compartment_map[compartment_name_wanted];
  vec=vec_map[parameter_name_wanted];
  size=vec.size()-1;
  value_wanted=vec[size];
  parameter_value=value_wanted;
  return parameter_value;
}
