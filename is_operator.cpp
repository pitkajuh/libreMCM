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
  bool rt=false;

  if(elem==add)
    {
      rt=true;
    }
  else if(elem==subtract)
    {
      rt=true;
    }
  else if(elem==multiply)
    {
      rt=true;
    }
  else if(elem==divide)
    {
      rt=true;
    }
  else if(elem==power)
    {
      rt=true;
    }
  else if(elem==open_parenthesis)
    {
      rt=true;
    }
  else if(elem==close_parenthesis)
    {
      rt=true;
    }
  else
    {
      rt=false;
    }

  return rt;
}
