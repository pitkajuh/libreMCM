/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <tuple>
#include "parse_compartment_equations.h"

using namespace std;

vector<tuple<
	     string, // compartment name
	     vector<
	            tuple<
	                  string, // parameter name
	                  vector<
	                  string // parameter values
	                 >
      >     >      >
      > params_graph;

void add_all_values ()
{
  int i=0, j=0, k=0;
  tuple<string, vector<tuple<string, string, int>>> val;
  string compartment_name, param_name, param_value;
  vector<tuple<string, string, int>> params;

  vector<string> parm_values;
  vector<tuple<string, vector<string>>> vec_add;
  tuple<string, vector<string>> tpl;

  while (i<=all_values.size ()-1)
    {
      val=all_values[i];
      compartment_name=get<0>(val);
      params=get<1>(val);

      while (j<=params.size ()-1)
	{
	  param_name=get<0>(params[j]);
	  param_value=get<1>(params[j]);
	  parm_values.push_back (param_value);
	  tpl=make_tuple (param_name, parm_values);
	  vec_add.push_back (tpl);
	  j++;
	}

      j=0;
      i++;
      params_graph.push_back (make_tuple(compartment_name, vec_add));
      vec_add.clear ();
      parm_values.clear ();
    }
}
