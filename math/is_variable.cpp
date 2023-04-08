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
#include "../global/global_constants.h"
#include "../util/is_in_vector.h"

const bool is_variable(string fchar)
{
  // Checks if string is variable (compartment).
  int i=0;
  const int size=fchar.size()-1;
  string fc;
  // cout<<"is_variable "<<fchar<<'\n';

  while(i<=size)
    {
      fc=fchar[i];

      if(fc==PARM_DELIM)
	{
	  fchar=fchar.substr(0, i);
	  break;
	}
      i++;
    }

  const bool result=is_in_vector(compartment_diagonal_v2, fchar);
  return result;
}
