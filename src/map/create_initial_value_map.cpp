/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../global/initial_value_map.h"
#include "../class/SplittedString.h"
#include "../global/compartment_diagonal_v2.h"
#include "../global/all_parameters.h"
#include "../global/global_constants.h"

void create_initial_value_map()
{
  string value;
  SplittedString splitted;

  for(const auto&i: compartment_diagonal_v2)
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
