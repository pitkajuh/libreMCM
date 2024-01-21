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

const string get_last_value(const SplittedString param)
{
  const string compartment_name_wanted=param.splitted_string_part1;
  const string parameter_name_wanted=param.splitted_string_part2;
  unordered_map<string, vector<string>> vec_map=compartment_map[compartment_name_wanted];
  const vector<string> vec=vec_map[parameter_name_wanted];
  return vec.back();
}
