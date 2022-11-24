/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <string>
#include <vector>
#include "values_to_graph.h"
#include "global.h"
#include "vector_convert.h"
#include "calculate_order_of_operations.h"
#include "read_sim_params.h"
#include "replace_in_vector.h"
#include "rk4.h"
#include "rk4_helpers.h"
#include "numerical_calculation_rules.h"
#include "helpers.h"
#include "numerical_calculation_begin.h"
#include "string_split.h"

using namespace std;

string comp_name_glob;
int jk=0;
double h;

vector<tuple<
	     string, // compartment name
	     vector<
	            tuple<
	                  string, // parameter name
	                  vector<
	                  string // parameter values
	                 >
      >     >      >
      > params_graph_up;

vector<vector<int>> numerical_calculation_order_of_operations;

void update_values(vector<string> result)
{
  int i=0;

  while(i<=params_graph.size()-1)
    {
      get<1>(get<1>(params_graph[i])[0]).push_back(result[i]);
      i++;
    }
  params_graph_up=params_graph;
}

vector<string> replace_in_equation1(vector<string> equation, int indices, string k_add)
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
		  replace=k_add;
		}
	      else
		{
		  replace=k_add;
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

string update_equations_sub_sub_routine(string compartment_name_split, vector<string> params)
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

vector<string> update_equations_subroutine(vector<string> equation, vector<int> indices, vector<string> values_to_add, vector<vector<string>> param_data)
{
  int i=0;
  tuple<string, string> param_splitted;
  string compartment_name_split, value, repl;
  vector<string> eq_params=param_data[jk];

  while(i<=indices.size()-1)
    {
      compartment_name_split=get<0>(split_string_in_two(eq_params[i], parm_delim));
      repl=update_equations_sub_sub_routine(compartment_name_split, values_to_add);
      equation=replace_in_equation1(equation, indices[i], repl);
      i++;
    }

  jk++;
  return equation;
}

vector<vector<string>> update_equations(vector<vector<string>> equations, vector<vector<int>> indices, vector<string> values_to_add, vector<vector<string>> param_data)
{
  int i=0;
  vector<vector<string>> rt;

  while(i<=equations.size()-1)
    {
      rt.push_back(update_equations_subroutine(equations[i], indices[i], values_to_add, param_data));
      i++;
    }
  return rt;
}

vector<string> get_values()
{
  int i=0, j=0, k=0;
  string comp_name, parameter_name;
  vector<string> parameters_empty;
  tuple<string, string> agh;
  vector<tuple<string, vector<string>>> empty_vec;
  vector<string> rt;

  while(i<=params_graph.size()-1)
    {
      comp_name=get<0>(params_graph[i]);
      empty_vec=get<1>(params_graph[i]);

      while(j<=empty_vec.size()-1)
	{
	  parameter_name=get<0>(empty_vec[j]);
	  parameters_empty=get<1>(empty_vec[j]);
	  agh=split_string_in_two(parameter_name, parm_delim);
	  comp_name=get<0>(agh);
	  parameter_name=get<1>(agh);
	  rt.push_back(parameters_empty[parameters_empty.size()-1]);

	  j++;
	}
      j=0;
      i++;
    }

  return rt;
}

vector<string> calculate_result(vector<string> k1, vector<string> k2, vector<string> k3, vector<string> k4, double h, vector<string> get_values_up)
{
  int i=0;
  vector<string> rt;
  double result;
  string result_str;

  while(i<=k1.size()-1)
    {
      result=(double) stod(get_values_up[i])+(stod(k1[i])+2*stod(k2[i])+2*stod(k3[i])+stod(k4[i]))/6;
      result_str=to_string(result);
      rt.push_back(result_str);
      i++;
    }

  return rt;
}

void calculate()
{
  int i=0, j=0;
  vector<tuple<string, tuple<vector<string>, vector<int>, vector<string>>, vector<int>, vector<string>, vector<string>>> aa;
  tuple<string, tuple<vector<string>, vector<int>, vector<string>>, vector<int>, vector<string>, vector<string>> bb;
  tuple<vector<string>, vector<int>, vector<string>> final_eq;
  vector<string> equation;
  vector<int> indices_for_ks;
  vector<string> parameter_data_for_indices, k1, k2, k3, k4;
  vector<vector<string>> equations;
  vector<vector<int>> indice_values;
  string comp_name_glob;
  vector<vector<string>> param_data;

  while(i<=for_calculation.size()-1)
    {
      aa=for_calculation[i];
      comp_name_glob=global_compartment_names[i];

      while(j<=aa.size()-1)
	{
	  bb=aa[j];
	  final_eq=get<1>(bb);
	  parameter_data_for_indices=get<2>(final_eq);
	  indices_for_ks=get<1>(final_eq);
	  equation=get<0>(final_eq);
	  numerical_calculation_order_of_operations.push_back(numerical_calculation_rules (equation));
	  equations.push_back(equation);
	  indice_values.push_back(indices_for_ks);
	  param_data.push_back(parameter_data_for_indices);
	  j++;
	}
      j=0;
      i++;
    }

  h=(double) 1/steps;
  h=(double) steps;
  double t=t_start;
  vector<string> result, get_val;
  string test1, test2, res;

  while(t<=t_end)
    {
      k1=k_calc(equations, indice_values, {" "}, "0", param_data, numerical_calculation_order_of_operations);
      k2=k_calc(equations, indice_values, k1, "0.5", param_data, numerical_calculation_order_of_operations);
      k3=k_calc(equations, indice_values, k2, "0.5", param_data, numerical_calculation_order_of_operations);
      k4=k_calc(equations, indice_values, k3, "0", param_data, numerical_calculation_order_of_operations);

      get_val=get_values();
      comp=0;
      result=calculate_result(k1, k2, k3, k4, h, get_val);

      equations=update_equations(equations, indice_values, result, param_data);
      update_values(result);

      jk=0;
      t=t+h;

    }
}
