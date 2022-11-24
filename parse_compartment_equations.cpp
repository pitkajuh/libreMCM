/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "get_compartment_equations.h"
#include "values_to_graph.h"

using namespace std;

vector<tuple<string, vector<string>, vector<string>>> equations_with_compartment_name;
vector<tuple<string, vector<tuple<string, string, int>>>> all_values;
vector<tuple<string, bool, vector<vector<string>>>> rt_local_global;

vector<tuple<string, vector<tuple<string, string, int>>>> parse_compartment_equations_subsubroutine()
{
  int i=0, j=0, k=0, half_life;
  string compartment_element_name, compartment_element_value;
  vector<tuple<string, string, int>> values;

  while(i<=compartment_parameters_rt.size()-1)
    {
      while(j<=get<1>(compartment_parameters_rt[i]).size()-1)
	{
	  while(k<=get<1>(compartment_parameters_rt[i])[j].size()-1)
	    {
	      compartment_element_name=get<0>(get<1>(compartment_parameters_rt[i])[j][k]);
	      compartment_element_value=get<1>(get<1>(compartment_parameters_rt[i])[j][k]);
	      half_life=get<2>(get<1>(compartment_parameters_rt[i])[j][k]);
	      values.push_back(make_tuple(compartment_element_name, compartment_element_value, half_life));
	      k++;
	    }
	  k=0;
	  j++;
	}
      all_values.push_back(make_tuple(get<0>(compartment_parameters_rt[i]), values));
      values.clear();
      j=0;
      i++;
    }

  add_all_values ();
  return all_values;
}

void parse_compartment_equations_subroutine(vector<vector<string>> compartment_vector)
{
  int i=0, j=0;
  string diagonal_element;

  // Get original compartment values
  while(i<=compartment_vector.size()-1)
    {
      diagonal_element=compartment_vector[i][i];
      equations_with_compartment_name.push_back(get_equations_compartment(compartment_vector, diagonal_element, i, i));
      i++;
    }
  parse_compartment_equations_subsubroutine();
}

void calculate_equation_with(vector<string> equations, bool equation_add, string compartment_name, int compartment_start_index)
{
  int i=0, j=0;

  while(i<=equations.size()-1)
    {
      if(equations.size()==0)
	{
	  break;
	}
      else
	{
	  rt_local_global.push_back(abc(equations[i], equation_add, compartment_name, compartment_start_index, 0));
	}
      i++;
    }
}

void parse_compartment_equations()
{
  int i=0;
  vector<string> equations_add, equations_subtract;
  string compartment_name, equation_add, equation_subtract;
  tuple<string, vector<string>, vector<string>> vector;
  parse_compartment_equations_subroutine(get_compartment_vector());

  while(i<=equations_with_compartment_name.size()-1)
    {
      vector=equations_with_compartment_name[i];
      compartment_name=get<0>(vector);
      equations_add=get<1>(vector);
      equations_subtract=get<2>(vector);

      if (compartment_name!=void_element and compartment_name!=origin_element)
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
