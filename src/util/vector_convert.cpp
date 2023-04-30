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

const vector<string> equation_string_to_equation_vector2(const string equation)
{
  int i=0;
  int nr_of_operators=0;
  int split_to;
  int i_to;
  const int size=equation.size()-1;
  bool op2_check;
  bool operator_check;
  bool is_empty;
  const char dummy='0';
  string empty="";
  string fchar;
  string fchar_prev;
  string str;
  vector<string> rt;
  string equation_temp=equation;
  fchar=equation[i];

  if(i==0 and fchar==SUBTRACT)
    {
      empty=fchar;
      i++;
    }

  while(i<=size)
    {
      fchar=equation[i];

      if(op2_check)
	{
	  split_to=equation_temp.find(CLOSE_PARENTHESIS);
	  equation_temp[split_to]=dummy;
	  i_to=split_to+1;

	  split_to=i_to-i;
	  str=equation.substr(i, split_to);
	  empty=empty+str;
	  i=i_to;
	  op2_check=false;
	  continue;
	}
      else
	{
	  operator_check=is_operator(fchar);

	  if(operator_check)
	    {
	      is_empty=empty.empty();

	      if(not is_empty)
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

	      if(empty==MATH_OP_PREFIX)
		{
		  op2_check=true;
		}
	    }
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

      if(not is_empty)
	{
	  rt.push_back(empty);
	}
    }
  return rt;
}

const vector<string> equation_string_to_equation_vector(const string equation)
{
  int i=0;
  int nr_of_operators=0;
  const int size=equation.size()-1;
  bool operator_check;
  bool is_empty;
  string empty="";
  string fchar;
  string fchar_prev;
  vector<string> rt;
  fchar=equation[i];

  if(i==0 and fchar==SUBTRACT)
    {
      empty=fchar;
      i++;
    }

  while(i<=size)
    {
      fchar=equation[i];
      operator_check=is_operator(fchar);

      if(operator_check)
	{
	  is_empty=empty.empty();

	  if(not is_empty)
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

      if(not is_empty)
	{
	  rt.push_back(empty);
	}
    }
  return rt;
}

const string vector_to_string(const vector<string> vec)
{
  string empty;
  bool is_empty;

  for(const auto&i: vec)
    {
      is_empty=i.empty();

      if(not is_empty)
	{
	  empty=empty+i;
	}
    }
  return empty;
}
