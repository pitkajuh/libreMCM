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
#include <string>
#include <vector>
#include "global.h"
#include "values_to_graph.h"
#include "calculate_order_of_operations.h"
#include "replace_in_vector.h"
#include "read_compartment_definition.h"
#include "vector_convert.h"
#include "rk4.h"
#include "string_split.h"
#include "helpers.h"

using namespace std;

int add_to_values_i=-1, add_to_values_j=-1;
int asd=0;

string get_last_value(string param)
{
  int i=0, j=0, k=0;
  string parameter_name, parameter_value, comp_name;
  vector<string> parameters_empty;
  vector<tuple<string, vector<string>>> empty_vec;
  bool found=false;
  tuple<string, string> fg=split_string_in_two(param, parm_delim), agh;
  string compartment_name_wanted=get<0>(fg), parameter_name_wanted=get<1>(fg);

  while(i<=params_graph.size()-1)
    {
      if(found)
	{
	  break;
	}

      comp_name=get<0>(params_graph[i]);
      empty_vec=get<1>(params_graph[i]);

      while(j<=empty_vec.size()-1)
	{
	  if(found)
	    {
	      break;
	    }

	  parameter_name=get<0>(empty_vec[j]);
	  parameters_empty=get<1>(empty_vec[j]);

	  agh=split_string_in_two(parameter_name, parm_delim);
	  comp_name=get<0>(agh);
	  parameter_name=get<1>(agh);

	  if(compartment_name_wanted==comp_name)
	    {
	      while(k<=parameters_empty[j].size()-1)
		{
		  if(parameter_name==parameter_name_wanted)
		    {
		      parameter_value=parameters_empty[parameters_empty.size()-1];
		      found=true;
		      break;
		    }
		  k++;
		}
	    }
	  k=0;
	  j++;
	}
      j=0;
      i++;
    }
  return parameter_value;
}

vector<string> get_multiple_last_values(vector<string> vec)
{
  int i=0;
  vector<string> rt;
  string str, str1;

  while(i<=vec.size()-1)
    {
      str=vec[i];
      str1=get_last_value(str);
      rt.push_back(str1);
      i++;
    }
  return rt;
}

// void get_param_and_comp(vector<string> vec)
// {
//   int i=0;
//   string compartment_name, params_name;
//   tuple<string, string> val;

//   while(i<=vec.size()-1)
//     {
//       val=get_compartment_parameter_value_subroutine(vec[i]);
//       compartment_name=get<0>(val);
//       params_name=get<1>(val);
//       i++;
//     }
// }

vector<string> replace_in_equation(vector<string> equation, int indices, string k_add)
{
  int i=0, j=0;
  string replace, k_add_1st;
  int equation_size=equation.size();

  while(i<=equation_size-1)
    {
      if(indices==i)
	{
	  if(equation[i-1]==multiply and equation[i+1]==multiply or equation[i-1]==multiply)
	    {
	      k_add_1st=k_add[0];
	      if(k_add_1st==subtract)
		{
		  replace=equation[i]+k_add;
		}
	      else
		{
		  replace=equation[i]+add+k_add;
		}
	      replace=calculate_order_of_operations(equation_string_to_equation_vector(replace));
	    }

	  equation=replace_in_vector(equation, replace, i, i);
	  equation_size=equation.size();
	}
      i++;
    }

  return equation;
}

string get_value_for_replace_whole_equation(string compartment_name_split, vector<string> params)
{
  int i=0;

  while(i<=global_compartment_names.size()-1)
    {
      if(compartment_name_split==global_compartment_names[i])
	{
	  break;
	}
      i++;
    }

  return params[i];
}

vector<string> replace_in_whole_equation(vector<string> equation, vector<int> indices, vector<string> params, string addition, vector<vector<string>> param_data)
{
  int i=0;
  tuple<string, string> param_splitted;
  string compartment_name_split, value, repl;
  vector<string> eq_params=param_data[asd];

  while(i<=indices.size()-1)
    {
      compartment_name_split=get<0>(split_string_in_two(eq_params[i], parm_delim));
      repl=get_value_for_replace_whole_equation(compartment_name_split, params);
      equation=replace_in_equation(equation, indices[i], repl);
      i++;
    }
  asd++;

  return equation;
}

vector<int> indices_update(vector<int> indices, int nr)
{
  int i=0;

  while(i<=indices.size()-1)
    {
      indices[i]=indices[i]+nr;
      i++;
    }
  return indices;
}

vector<int> indices_update2(vector<int> indices, int nr)
{
  int i=0;

  while(i<=indices.size()-1)
    {
      if(indices[i]!=1)
	{
	  indices[i]=indices[i]-nr;
	}
      i++;
    }
  return indices;
}

vector<string> combine_string_vectors(vector<string> combine1, vector<string> combine2)
{
  int i=0;

  while(i<=combine2.size()-1)
    {
      combine1.push_back(combine2[i]);
      i++;
    }
  return combine1;
}

vector<int> combine_int_vectors(vector<int> combine1, vector<int> combine2)
{
  int i=0;

  while(i<=combine2.size()-1)
    {
      combine1.push_back(combine2[i]);
      i++;
    }

  return combine1;
}

int comp=0;

tuple<vector<string>, vector<int>> parse_values_numerical(vector<string> parameter_data_for_indices, vector<int> indices)
{
  int i=0;
  tuple<string, string> splitting;
  string compartment_name, parameter_name;
  string compartment_name_global=global_compartment_names[comp];
  vector<int> empty;
  vector<vector<int>> new_indices;

  while(i<=parameter_data_for_indices.size()-1)
    {
      splitting=split_string_in_two(parameter_data_for_indices[i], parm_delim);
      compartment_name=get<0>(splitting);
      parameter_name=get<1>(splitting);
      i++;
    }

  comp++;

  return make_tuple(parameter_data_for_indices, indices);
}

vector<string> values_to_add_update(vector<string> values_to_add, string constant)
{
  int i=0;
  double result;
  string zero="0";

  if(constant!=zero)
    {
      while(i<=values_to_add.size()-1)
	{
	  result=stod(constant)*stod(values_to_add[i]);
	  values_to_add[i]=to_string(result);
	  i++;
	}
    }

  return values_to_add;
}

string order_of_operations (vector<string> equation, vector<int> math_op_ind)
{
  int i=0;
  string math_operator, value1, value2, result;

  while (i<=math_op_ind.size()-1)
    {
      if(equation.size()==1)
	{
	  break;
	}

      math_operator=equation[math_op_ind[i]];
      value1=equation[math_op_ind[i]-1];
      value2=equation[math_op_ind[i]+1];
      result=get_math_operator (value1, value2, math_operator);
      equation=replace_in_vector (equation, result, math_op_ind[i]-1, math_op_ind[i]+1);
      math_op_ind=indices_update2 (math_op_ind, 2);
      i++;
    }

  return equation[0];
}

double k_test(vector<string> equation, vector<int> indices, vector<string> values_to_add, string constant, vector<vector<string>> param_data, vector<int> numerical_calculation_order_of_operations)
{
  int i=0;

  if(values_to_add.size()>1)
    {
      values_to_add=values_to_add_update(values_to_add, constant);
      equation=replace_in_whole_equation(equation, indices, values_to_add, constant, param_data);
    }

  return stod(order_of_operations (equation, numerical_calculation_order_of_operations));
}

void add_to_values(string value_to_add)
{
  int i=0, j=0;
  string parameter_name, parameter_value, comp_name;
  vector<string> parameters_empty;
  vector<tuple<string, vector<string>>> empty_vec;
  bool added=false;

  if(add_to_values_i!=-1 and add_to_values_j!=-1)
    {
      get<1>(get<1>(params_graph[add_to_values_i])[add_to_values_j]).push_back(value_to_add);
    }
  else
    {
      while(i<=params_graph.size()-1)
	{
	  comp_name=get<0>(params_graph[i]);
	  empty_vec=get<1>(params_graph[i]);

	  if(added)
	    {
	      break;
	    }

	  while(j<=empty_vec.size()-1)
	    {
	      parameter_name=get<0>(empty_vec[j]);
	      parameters_empty=get<1>(empty_vec[j]);

	      if(added)
		{
		  break;
		}
	      else if(global_compartment_names[i]==comp_name)
		{
		  add_to_values_i=i;
		  add_to_values_j=j;
		  parameter_value=parameters_empty[parameters_empty.size()-1];
		  added=true;
		}
	      j++;
	    }
	  j=0;
	  i++;
	}
    }
}

tuple<vector<string>, vector<int>, vector<string>> combine_equations_and_indices(vector<tuple<vector<string>, vector<int>, bool, vector<string>>> vector1)
{
  int i=0;
  vector<string> equation, final_eq, parameter_data_for_indices, parameter_data_for_indices_final;
  vector<int> indices, indices_final;
  bool add_or_not;

  while(i<=vector1.size()-1)
    {
      equation=get<0>(vector1[i]);
      indices=get<1>(vector1[i]);
      add_or_not=get<2>(vector1[i]);
      parameter_data_for_indices=get<3>(vector1[i]);

      if(add_or_not)
	{
	  if(i==0)
	    {
	      final_eq=combine_string_vectors(final_eq, equation);
	      indices_final=indices;
	      parameter_data_for_indices_final=parameter_data_for_indices;
	    }
	  else
	    {
	      equation.insert(equation.begin(), add);
	      indices=indices_update(indices, 1+final_eq.size());
	      indices_final=combine_int_vectors(indices_final, indices);
	      parameter_data_for_indices_final=combine_string_vectors(parameter_data_for_indices_final, parameter_data_for_indices);
	      final_eq=combine_string_vectors(final_eq, equation);
	    }
	}
      else
	{
	  equation.insert(equation.begin(), subtract);
	  indices=indices_update(indices, 1+final_eq.size());
	  indices_final=combine_int_vectors(indices_final, indices);
	  parameter_data_for_indices_final=combine_string_vectors(parameter_data_for_indices_final, parameter_data_for_indices);
	  final_eq=combine_string_vectors(final_eq, equation);
	}
      i++;
    }

  return make_tuple(final_eq, indices_final, parameter_data_for_indices_final);
}
