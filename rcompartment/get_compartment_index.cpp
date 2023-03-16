/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "read_compartment.h"

int get_compartment_index(string compartment_name)
{
  int j=0;
  int compartment_index=-1;

  for(const auto&i: compartment_diagonal)
    {
      if(i==compartment_name)
	{
	  compartment_index=j;
	  break;
	}
      j++;
    }
  return compartment_index;
}
