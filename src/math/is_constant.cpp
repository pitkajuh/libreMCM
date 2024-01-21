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
#include "../global/equation_constants.h"
#include "../util/is_in_vector.h"

const bool is_constant(string fchar)
{
  bool result=false;
  const int size=fchar.size();
  string neg;

  neg=fchar[0];

  // Check if trying to get a negative value of a constant.
  if(neg==SUBTRACT)
    {
      fchar=fchar.substr(1, size);
    }

  result=is_in_vector(equation_constants, fchar);
  return result;
}
