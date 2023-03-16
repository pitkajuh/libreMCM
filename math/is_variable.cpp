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
#include "../util/vector_convert.h"

bool is_variable(const string fchar)
{
  int i=0;
  int j=0;
  const int size=compartment_diagonal.size();
  bool fchar_is_variable=false;
  vector<string> rt=equation_string_to_equation_vector(fchar);
  const int rt_size=rt.size();
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
