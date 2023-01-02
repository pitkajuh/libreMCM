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
#include "is_operator.h"
#include "replace_in_vector.h"
#include "read_bin.h"
#include "calculate_order_of_operations.h"
#include "parse_compartment_equations.h"

using namespace std;

vector<string> equation_str_to_vec(string equation)
{
  int i=0;
  const string empty_str="";
  string empty=empty_str;
  string fchar;
  vector<string> rt;

  while(i<=equation.size()-1)
    {
      fchar=equation[i];

      if(is_operator(fchar))
	{
	  rt.push_back(empty);
	  rt.push_back(fchar);
	  empty=empty_str;
	}
      else
	{
	  empty=empty+fchar;
	}
      i++;
    }

  rt.push_back(empty);

  return rt;
}

int get_compartment_index(string compartment_name)
{
  int i=0;
  int compartment_index;
  bool found=false;
  string compartment_name_comp;
  tuple<string, vector<string>, vector<string>> equation_with_compartment_name;

  while(i<=equations_with_compartment_name.size()-1)
    {
      equation_with_compartment_name=equations_with_compartment_name[i];
      compartment_name_comp=get<0>(equation_with_compartment_name);

      if(compartment_name==compartment_name_comp)
	{
	  compartment_index=i;
	  found=true;
	  break;
	}
      i++;
    }

  if(!found)
    {
      compartment_index=-1;
    }

  return compartment_index;
}

void calculate_with_parameters(vector<string> equation_vector, int calculate_from_index, int calculate_to_index, string compartment_name)
{
  int compartment_index=get_compartment_index(compartment_name);

  if(compartment_index!=-1)
    {
      int i=compartment_index;
      int j=0;
      int half_life;
      string parameter_name;
      string parameter_value;
      string compartment_name_change;
      tuple<string, vector<tuple<string, string, int>>> all_values_i;
      vector<tuple<string, string, int>> all_values_i_j;
      tuple<string, vector<tuple<string, string, int>>> all_values_comp_i=all_values[compartment_index];
      vector<tuple<string, string, int>> parameters=get<1>(all_values_comp_i);
      tuple<string, string, int> parameters_j;

      while(i<=all_values.size()-1)
	{
	  all_values_i=all_values[i];
	  compartment_name_change=get<0>(all_values_i);

	  if(compartment_name_change==compartment_name)
	    {
	      all_values_i_j=get<1>(all_values_i);

	      while(j<=all_values_i_j.size()-1)
		{
		  compartment_name_change=get<0>(all_values_i);
		  parameters_j=parameters[j];
		  parameter_name=get<0>(parameters_j);
		  parameter_value=get<1>(parameters_j);
		  half_life=get<2>(parameters_j);
		  j++;
		}
	      j=0;
	    }
	  i++;
	}
    }
}

vector<tuple<string, string, int>> get_compartment_elements_by_compartment_name(string compartment_name)
{
  int i=0;
  vector<tuple<string, string, int>> compartment_values;
  tuple<string, vector<tuple<string, string, int>>> all_values_i;
  string compartment_name_comp;

  while(i<=all_values.size()-1)
    {
      all_values_i=all_values[i];
      compartment_name_comp=get<0>(all_values_i);

      if(compartment_name==compartment_name_comp)
	{
	  compartment_values=get<1>(all_values_i);
	  break;
	}
      i++;
    }

  return compartment_values;
}

vector<vector<string>> global_equations;
int start_from=0;

void params4(vector<tuple<string, string, int>> compartments_parameters, int index_replace)
{
  int i=0;
  string compartment_parameter_name;
  vector<vector<string>> rt;
  tuple<string, string, int> compartment_parameters_i;
  vector<string> global_equation;

  while(i<=global_equations.size()-1)
    {
      compartment_parameters_i=compartments_parameters[i];
      compartment_parameter_name=get<0>(compartment_parameters_i);
      global_equation=global_equations[i];
      global_equations[i]=replace_in_vector(global_equation, compartment_parameter_name, index_replace, index_replace);
      i++;
    }
}

vector<string> params3(vector<tuple<string, string, int>> compartments_parameters, vector<string> equation_vector, int index_replace)
{
  int i=start_from;
  string compartment_parameter_name;
  tuple<string, string, int> compartments_parameters_i;

  while(i<=compartments_parameters.size()-1)
    {
      compartments_parameters_i=compartments_parameters[i];
      compartment_parameter_name=get<0>(compartments_parameters_i);
      equation_vector=replace_in_vector(equation_vector, compartment_parameter_name, index_replace, index_replace);
      global_equations.push_back(equation_vector);
      i++;
    }
  return equation_vector;
}

int j_global=0;

void params2(vector<int> indices, vector<string> equation_vector, vector<vector<tuple<string, string, int>>> compartments_parameters)
{
  int i=0;
  int i_prev;
  int indice;
  vector<tuple<string, string, int>> parameters;
  string equation_i;

  while(i<=indices.size()-1)
    {
      indice=indices[i];
      equation_i=equation_vector[indice];
      parameters=get_compartment_elements_by_compartment_name(equation_i);

      if(i!=i_prev and global_equations.size()>=1)
	{
	  params4(parameters, indice);
	}
      else
	{
	  equation_vector=params3(parameters, equation_vector, indice);
	}
      i_prev=i;
      i++;
    }
}

tuple<string, bool, vector<vector<string>>> abc(string equation, bool equation_add, string compartment_name, int compartment_start_index, int index1)
{
  vector<string> equation_vector=equation_str_to_vec(equation);
  int i=0;
  int compartment_index;
  string eq;
  int found=0;
  vector<int> indices;
  tuple<string, bool, vector<vector<string>>> rt;
  vector<
    vector<tuple<string, string, int>>
    > compartments_parameters;
  bool operator_or_not;
  bool numerical_value_or_not;

  while(i<=equation_vector.size()-1)
    {
      eq=equation_vector[i];
      operator_or_not=is_operator(eq);
      numerical_value_or_not=is_string_numerical_value(eq);

      if(!operator_or_not and !numerical_value_or_not)
	{
	  compartment_index=get_compartment_index(eq);

	  if(compartment_index!=-1)
	    {
	      indices.push_back(i);
	    }
	}
      i++;
    }

  j_global=0;
  params2(indices, equation_vector, compartments_parameters);
  rt=make_tuple(compartment_name, equation_add, global_equations);
  global_equations.clear();

  return rt;
}
