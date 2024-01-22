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

const string mcm_log(const string value)
{
  const double value_d=s2d(value);

  if(value_d==0){throw std::invalid_argument("Invalid input for natural logarithm: "+value+". The input must differ from zero.");}

  const double result=log(value_d);
  const string result_str=d2str(result);
  return result_str;
}
