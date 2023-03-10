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
  int i=0;
  int size=compartment_diagonal.size();
  int compartment_index=-1;
  string compartment;

  while(i<=size-1)
    {
      compartment=compartment_diagonal[i];

      if(compartment==compartment_name)
	{
	  compartment_index=i;
	  break;
	}
      i++;
    }
  return compartment_index;
}
