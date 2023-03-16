/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <map>
#include "../global/global.h"
#include "../wdata/values_to_graph.h"
#include "../class/SplittedString.h"

using std::map;

map<string, SplittedString> initial_value_map;

void create_initial_value_map()
{
  string value;
  SplittedString splitted;

  for(const auto&i: all_compartments)
    {
      for(const auto&j: all_parameters)
	{
	  value=i+PARM_DELIM+j;
	  splitted.splitted_string_part1=i;
	  splitted.splitted_string_part2=j;
	  initial_value_map[value]=splitted;
	}
    }
}
