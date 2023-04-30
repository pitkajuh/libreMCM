/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <cmath>
#include "../util/d2str.h"
#include "../util/s2d.h"

const string mcm_power(const string value, const string exponent)
{
  const double value_d=s2d(value);
  const double exponent_d=s2d(exponent);
  const double result=pow(value_d, exponent_d);
  const string result_str=d2str(result);
  return result_str;
}
