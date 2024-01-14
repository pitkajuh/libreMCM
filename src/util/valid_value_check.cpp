/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <iostream>
#include "s2d.h"

using std::cerr;

const double value_check(const string value)
{
  try
    {
      const double value_check=s2d(value);
      return value_check;
    }
  catch(const std::invalid_argument&)
    {
      cerr<<"ERROR, "+value+" is not valid numerical value.\n";
      throw;
    }
}
