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
  const size_t f=fchar.find(PARM_DELIM);
  const size_t f1=string::npos;

  if(f!=f1)
    {
      const int i=static_cast<int>(f);
      fchar=fchar.substr(0, i);
    }

  const bool result=is_in_vector(compartment_diagonal_v2, fchar);
  return result;
}
