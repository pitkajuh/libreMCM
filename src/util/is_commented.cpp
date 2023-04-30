/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../global/global_constants.h"

#include <iostream>

using std::cout;

const bool is_commented(const string line)
{
  const int size=line.size()-1;
  bool commented_or_not=false;

  if(size>0)
    {
      string line_com=line.substr(0, 2);

      if(line_com==COMMENT)
	{
	  commented_or_not=true;
	}
    }
  return commented_or_not;
}
