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

void value_check(const string value)
{
  try
    {
      const double asd=s2d(value);
    }
  catch(const std::invalid_argument&)
    {
      cerr<<"ERROR, "+value+" is not valid numerical value.\n";
      throw;
    }
}
