/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "is_operator.h"
#include "../rcompartment/read_compartment.h"

vector<string> is_variable_helper(string line)
{
  int i=0;
  int size=line.size();
  const string empty_str="";
  vector<string> rt;
  string fchar;
  string empty=empty_str;
  bool is_operator_or_not;

  while(i<=size-1)
    {
      fchar=line[i];
      is_operator_or_not=is_operator(fchar);

      if(i==size-1)
	{
	  rt.push_back(fchar);
	}
      else if(is_operator_or_not)
	{
	  rt.push_back(empty);
	  rt.push_back(fchar);
	  empty=empty_str;
	  i++;
	  continue;
	}
      else
	{
	  empty=empty+fchar;
	}
      i++;
    }
  return rt;
}

bool is_variable(string fchar)
{
  int i=0;
  int j=0;
  int size=compartment_diagonal.size();
  bool fchar_is_variable=false;
  vector<string> rt=is_variable_helper(fchar);
  int rt_size=rt.size();
  string rt_j;
  string variables_i;

  while(i<=size-1)
    {
      if(fchar_is_variable)
	{
	  break;
	}
      while(j<=rt_size-1)
	{
	  rt_j=rt[j];
	  variables_i=compartment_diagonal[i];

	  if(rt_j==variables_i)
	    {
	      fchar_is_variable=true;
	      break;
	    }
	  j++;
	}
      j=0;
      i++;
    }
  return fchar_is_variable;
}
