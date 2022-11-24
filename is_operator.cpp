/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "global.h"

using namespace std;

bool is_operator(string elem)
{
  if(elem==add)
    {
      return true;
    }
  else if(elem==subtract)
    {
      return true;
    }
  else if(elem==multiply)
    {
      return true;
    }
  else if(elem==divide)
    {
      return true;
    }
  else if(elem==power)
    {
      return true;
    }
  else if(elem==open_parenthesis)
    {
      return true;
    }
  else if(elem==close_parenthesis)
    {
      return true;
    }
  else
    {
      return false;
    }
}
