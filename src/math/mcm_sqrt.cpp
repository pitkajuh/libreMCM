/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <stdexcept>
#include <cmath>
#include "../util/d2str.h"
#include "../util/s2d.h"

const string mcm_sqrt(const string value)
{
  const double value_d=s2d(value);

  if(value_d<0)
    {
      throw std::invalid_argument("Invalid input for square root: "+value+". Input for square root must be a positive number.");
    }

  const double exponent_d=0.5;
  const double result=pow(value_d, exponent_d);
  const string result_str=d2str(result);
  return result_str;
}
