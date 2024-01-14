/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../global/num_method.h"
#include "../global/num_methods.h"
#include "../util/is_in_vector.h"

void solver_valid(const string value)
{
  // Check if the defined numerical method was valid.
  const bool num_method_defined=is_in_vector(available_num_methods, value);

  if(num_method_defined)
    {
      num_method=value;
    }
  else
    {
      printf("Numerical method (num_method) was not defined, using default setting (rk4).\n");
      num_method=RK4; // Temporary. At the moment only one numerical method is defined. Will be removed when there are more.
    }
}
