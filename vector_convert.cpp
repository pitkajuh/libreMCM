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
#include <vector>
#include "global.h"
#include "is_operator.h"

using namespace std;

vector<string> equation_string_to_equation_vector(string equation)
{
  int i=0, nr_of_operators=0;
  string empty="", fchar;
  vector<string> rt;

  while(i<=equation.size()-1)
    {
      fchar=equation[i];

      if(is_operator(fchar))
	{
	  rt.push_back(empty);
	  rt.push_back(fchar);
	  empty="";
	  nr_of_operators++;
	}
      else
	{
	  empty=empty+fchar;
	}
      i++;
    }

  if(nr_of_operators==0)
    {
      rt.push_back(equation);
    }
  else
    {
      rt.push_back(empty);
    }

  return rt;
}
