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
  int i=0;
  int nr_of_operators=0;
  const string empty_str="";
  string empty=empty_str;
  string fchar;
  vector<string> rt;
  bool is_operator_or_not;

  while(i<=equation.size()-1)
    {
      fchar=equation[i];
      is_operator_or_not=is_operator(fchar);

      if(is_operator_or_not)
	{
	  rt.push_back(empty);
	  rt.push_back(fchar);
	  empty=empty_str;
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
