/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "global.h"
#include "get_compartment_equations.h"
#include "values_to_graph.h"

using namespace std;

vector<tuple<string, vector<string>, vector<string>>> equations_with_compartment_name;
vector<tuple<string, vector<tuple<string, string, int>>>> all_values;
vector<tuple<string, bool, vector<vector<string>>>> rt_local_global;

vector<tuple<string, vector<tuple<string, string, int>>>> parse_compartment_equations_subsubroutine()
{
  int i=0;
  int j=0;
  int k=0;
  int half_life;
  string compartment_element_name;
  string compartment_element_value;
  vector<tuple<string, string, int>> values;
  tuple<string, string, int> values_i;
  tuple<string, vector<vector<tuple<string, string, int>>>> compartment_parameters_i;
  vector<vector<tuple<string, string, int>>> compartment_parameters_i1;
  vector<tuple<string, string, int>> compartment_parameters_i1_j;
  tuple<string, string, int> compartment_parameters_i1_j_k;
  tuple<string, vector<tuple<string, string, int>>> add_values_i;
  string name;

  while(i<=compartment_parameters_rt.size()-1)
    {
      compartment_parameters_i=compartment_parameters_rt[i];
      compartment_parameters_i1=get<1>(compartment_parameters_i);

      while(j<=compartment_parameters_i1.size()-1)
	{
	  compartment_parameters_i1_j=compartment_parameters_i1[j];

	  while(k<=compartment_parameters_i1_j.size()-1)
	    {
	      compartment_parameters_i1_j_k=compartment_parameters_i1_j[k];
	      compartment_element_name=get<0>(compartment_parameters_i1_j_k);
	      compartment_element_value=get<1>(compartment_parameters_i1_j_k);
	      half_life=get<2>(compartment_parameters_i1_j_k);
	      values_i=make_tuple(compartment_element_name, compartment_element_value, half_life);
	      values.push_back(values_i);
	      k++;
	    }
	  k=0;
	  j++;
	}
      name=get<0>(compartment_parameters_i);
      add_values_i=make_tuple(name, values);
      all_values.push_back(add_values_i);
      values.clear();
      j=0;
      i++;
    }

  add_all_values();
  return all_values;
}

void parse_compartment_equations_subroutine(vector<vector<string>> compartment_vector)
{
  int i=0;
  int j=0;
  string diagonal_element;
  tuple<string, vector<string>, vector<string>> compartment_equations;

  // Get original compartment values
  while(i<=compartment_vector.size()-1)
    {
      diagonal_element=compartment_vector[i][i];
      compartment_equations=get_equations_compartment(compartment_vector, diagonal_element, i, i);
      equations_with_compartment_name.push_back(compartment_equations);
      i++;
    }
  parse_compartment_equations_subsubroutine();
}

void calculate_equation_with(vector<string> equations, bool equation_add, string compartment_name, int compartment_start_index)
{
  int i=0;
  int j=0;
  string equation;
  tuple<string, bool, vector<vector<string>>> abc_result;

  while(i<=equations.size()-1)
    {
      equation=equations[i];

      if(equations.size()==0)
	{
	  break;
	}
      else
	{
	  abc_result=abc(equation, equation_add, compartment_name, compartment_start_index, 0);
	  rt_local_global.push_back(abc_result);
	}
      i++;
    }
}

void parse_compartment_equations()
{
  int i=0;
  vector<string> equations_add;
  vector<string> equations_subtract;
  string compartment_name;
  tuple<string, vector<string>, vector<string>> vector;
  parse_compartment_equations_subroutine(get_compartment_vector());

  while(i<=equations_with_compartment_name.size()-1)
    {
      vector=equations_with_compartment_name[i];
      compartment_name=get<0>(vector);
      equations_add=get<1>(vector);
      equations_subtract=get<2>(vector);

      if(compartment_name!=void_element and compartment_name!=origin_element)
	{
	  if(equations_add.size()>0)
	    {
	      calculate_equation_with(equations_add, true, compartment_name, i);
	    }
	  if(equations_subtract.size()>0)
	    {
	      calculate_equation_with(equations_subtract, false, compartment_name, i);
	    }
	}
      i++;
    }
}
