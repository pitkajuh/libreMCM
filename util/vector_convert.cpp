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
#include "../math/is_operator.h"

vector<string> equation_string_to_equation_vector(const string equation)
{
  int i=0;
  const int size=equation.size();
  int nr_of_operators=0;
  string empty="";
  string fchar;
  string fchar_prev;
  vector<string> rt;
  bool is_operator_or_not;
  bool is_empty;
  fchar=equation[i];

  if(i==0 and fchar==SUBTRACT)
    {
      empty=fchar;
      i++;
    }

  while(i<=size-1)
    {
      fchar=equation[i];
      is_operator_or_not=is_operator(fchar);

      if(is_operator_or_not)
	{
	  is_empty=empty.empty();

	  if(!is_empty)
	    {
	      rt.push_back(empty);
	    }

	  if(fchar==SUBTRACT and i>0)
	    {
	      if(fchar_prev==POWER)
		{
		  empty=SUBTRACT;
		}
	      else
		{
		  rt.push_back(ADD);
		  empty=SUBTRACT;
		}

	      nr_of_operators++;
	      i++;
	      continue;
	    }
	  rt.push_back(fchar);
	  empty="";
	  nr_of_operators++;
	}
      else
	{
	  empty=empty+fchar;
	}
      i++;
      fchar_prev=fchar;
    }
  if(nr_of_operators==0)
    {
      rt.push_back(equation);
    }
  else
    {
      is_empty=empty.empty();

      if(!is_empty)
	{
	  rt.push_back(empty);
	}
    }
  return rt;
}

string vector_to_string(const vector<string> vec)
{
  string empty;
  bool is_empty;

  for(const auto&i: vec)
    {
      is_empty=i.empty();

      if(!is_empty)
	{
	  empty=empty+i;
	}
    }
  return empty;
}
