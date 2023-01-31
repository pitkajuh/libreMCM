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
#include "../global/global.h"
#include "../math/is_operator.h"

using namespace std;

vector<string> equation_string_to_equation_vector(string equation)
{
  int i=0;
  int nr_of_operators=0;
  const string empty_str="";
  string empty=empty_str;
  string fchar;
  string fchar_prev;
  vector<string> rt;
  bool is_operator_or_not;

  while(i<=equation.size()-1)
    {
      fchar=equation[i];
      is_operator_or_not=is_operator(fchar);

      if(is_operator_or_not)
	{
	  if(!empty.empty())
	    {
	      rt.push_back(empty);
	    }

	  if(fchar==subtract and i>0)
	    {
	      fchar_prev=fchar;
	      rt.push_back(add);
	      empty=subtract;
	      nr_of_operators++;
	      i++;
	      continue;
	    }

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
      if(!empty.empty())
	{
	  rt.push_back(empty);
	}
    }

  return rt;
}

string vector_to_string(vector<string> vec)
{
  int i=0;
  string empty;
  string fchar;

  while(i<=vec.size()-1)
    {
      fchar=vec[i];

      if(!fchar.empty())
	{
	  empty=empty+fchar;
	}
      i++;
    }

  return empty;
}
