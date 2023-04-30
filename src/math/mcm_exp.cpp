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

const string mcm_exp(const string value)
{
  const double value_d=s2d(value);
  const double result=exp(value_d);
  const string result_str=d2str(result);
  return result_str;
}
