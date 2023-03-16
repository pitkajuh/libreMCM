/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../global/global.h"

bool is_operator(const string elem)
{
  bool rt=false;

  if(elem==ADD)
    {
      rt=true;
    }
  else if(elem==SUBTRACT)
    {
      rt=true;
    }
  else if(elem==MULTIPLY)
    {
      rt=true;
    }
  else if(elem==DIVIDE)
    {
      rt=true;
    }
  else if(elem==POWER)
    {
      rt=true;
    }
  else if(elem==OPEN_PARENTHESIS)
    {
      rt=true;
    }
  else if(elem==CLOSE_PARENTHESIS)
    {
      rt=true;
    }
  else
    {
      rt=false;
    }
  return rt;
}
