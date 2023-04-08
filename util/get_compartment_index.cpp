/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../global/compartment_diagonal_v2.h"

const int get_compartment_index(const string compartment_name)
{
  int j=0;

  for(const auto&i: compartment_diagonal_v2)
    {
      if(i==compartment_name)
	{
	  break;
	}
      j++;
    }
  return j;
}
