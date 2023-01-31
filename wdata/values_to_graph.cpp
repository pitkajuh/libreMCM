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
#include <tuple>
#include "../eqs/parse_compartment_equations.h"

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

void add_all_values()
{
  int i=0;
  int j=0;
  tuple<string, vector<tuple<string, string, int>>> val;
  string compartment_name;
  string param_name;
  string param_value;
  vector<tuple<string, string, int>> params;
  tuple<string, string, int> params_j;
  vector<string> parm_values;
  vector<tuple<string, vector<string>>> vec_add;
  tuple<string, vector<string>> tpl;

  tuple<
	     string, // compartment name
	     vector<
	            tuple<
	                  string, // parameter name
	                  vector<
	                  string // parameter values
	                 >
      >     >      >
       params_graph_i;

  while(i<=all_values.size()-1)
    {
      val=all_values[i];
      compartment_name=get<0>(val);
      params=get<1>(val);

      while(j<=params.size()-1)
	{
	  params_j=params[j];
	  param_name=get<0>(params_j);
	  param_value=get<1>(params_j);

	  parm_values.push_back(param_value);
	  tpl=make_tuple(param_name, parm_values);
	  vec_add.push_back(tpl);
	  parm_values.clear();
	  j++;
	}

      j=0;
      i++;

      params_graph_i=make_tuple(compartment_name, vec_add);
      params_graph.push_back(params_graph_i);

      vec_add.clear();
      parm_values.clear();
    }
}
