/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <vector>
#include "global.h"

using namespace std;

vector<int> numerical_calculation_rules(vector<string> fa)
{
  int i=0, j=0;
  string fchar, math_operator;
  vector<string> operators={power, divide, multiply, add, subtract};
  vector<int> numerical_calculation_rules_rt;

  while (i<=operators.size ()-1)
    {
      math_operator=operators[i];

      while (j<=fa.size ()-1)
	{
	  fchar=fa[j];

	  if (math_operator==fchar)
	    {
	      numerical_calculation_rules_rt.push_back (j);
	    }
	  j++;
	}

      j=0;
      i++;
    }

  return numerical_calculation_rules_rt;
}
