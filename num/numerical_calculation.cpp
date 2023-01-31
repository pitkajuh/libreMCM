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
#include "rk4.h"
#include "numerical_calculation_rules.h"
#include "numerical_calculation_begin.h"
#include "../rcompartment/read_compartment_definition.h"
#include "../wdata/values_to_graph.h"
#include "../global/global.h"
#include "../util/vector_convert.h"
#include "../util/replace_in_vector.h"
#include "../util/string_split.h"
#include "../math/calculate_order_of_operations.h"
#include "../rcfg/read_sim_params.h"
#include "../eqs/equations_sort.h"

using namespace std;

string comp_name_glob;
int jk=0;
double h;
int comp=0;

vector<tuple<string, vector<tuple<string, vector<string>>>>> params_graph_up;
vector<vector<int>> numerical_calculation_order_of_operations;
vector<vector<string>> equations_sorted;
vector<vector<int>> numerical_calculation_order_of_operations_sorted;
vector<vector<int>> indice_values_sorted;
vector<vector<string>> param_data_sorted;

void update_values(vector<string> result)
{
  int i=0;
  int j=0;
  int k=0;
  string name;
  vector<tuple<string, vector<string>>> empty_vec;

  tuple<
    string, // compartment name
    vector<
      tuple<
	string, // parameter name
	vector<
	  string // parameter values
	  >
	>     >      >
    params_graph_up_i;

  string result_k;
  tuple<string, vector<string>> empty_vec_j;
  vector<string> empty_vec_j_1;

  while(i<=params_graph.size()-1)
    {
      params_graph_up_i=params_graph[i];
      name=get<0>(params_graph_up_i);
      empty_vec=get<1>(params_graph_up_i);

      while(j<=empty_vec.size()-1)
	{
	  result_k=result[k];
	  get<1>(get<1>(params_graph[i])[j]).push_back(result_k);

	  j++;
	  k++;
	}
      j=0;
      i++;
    }

  params_graph_up=params_graph;
}

string update_equations_sub_sub_routine(string compartment_name_split, vector<string> params)
{
  int i=0;
  int indice_found;
  string compartment_name;
  string params_rt;

  while(i<=global_compartment_names.size()-1)
    {
      compartment_name=global_compartment_names[i];

      if(compartment_name_split==compartment_name)
	{
	  indice_found=i;
	  break;
	}
      i++;
    }

  params_rt=params[indice_found];
  return params_rt;
}

vector<string> update_equations_subroutine(vector<string> equation, vector<int> indices, vector<string> values_to_add, vector<vector<string>> param_data)
{
  int i=0;
  tuple<string, string> param_splitted;
  string compartment_name_split;
  string value;
  string equations_updated;
  vector<string> eq_params=param_data[jk];
  string eq_params_i;
  int indice;
  tuple<string, string> string_splitted;

  while(i<=indices.size()-1)
    {
      indice=indices[i];
      eq_params_i=eq_params[i];
      string_splitted=split_string_in_two(eq_params_i, parm_delim);
      compartment_name_split=get<0>(string_splitted);

      equations_updated=update_equations_sub_sub_routine(compartment_name_split, values_to_add);
      equation=replace_in_vector(equation, equations_updated, indice, indice);
      i++;
    }

  jk++;

  return equation;
}

vector<vector<string>> update_equations(vector<vector<string>> equations, vector<vector<int>> indices, vector<string> values_to_add, vector<vector<string>> param_data)
{
  int i=0;
  vector<vector<string>> rt;
  vector<string> update_eq_sub;
  vector<string> equation;
  vector<int> indice;

  while(i<=equations.size()-1)
    {
      equation=equations[i];
      indice=indices[i];
      update_eq_sub=update_equations_subroutine(equation, indice, values_to_add, param_data);
      rt.push_back(update_eq_sub);
      i++;
    }

  return rt;
}

vector<string> get_values()
{
  int i=0;
  int j=0;
  int k=0;
  string comp_name;
  string parameter_name;
  vector<string> parameters_empty;
  tuple<string, string> agh;
  vector<tuple<string, vector<string>>> empty_vec;
  vector<string> rt;

  tuple<
    string, // compartment name
    vector<
      tuple<
	string, // parameter name
	vector<
	  string // parameter values
	  >
	>     >      >
    params_graph_up_i;

  tuple<string, vector<string>> empty_vec_j;

  while(i<=params_graph.size()-1)
    {
      params_graph_up_i=params_graph[i];
      comp_name=get<0>(params_graph_up_i);
      empty_vec=get<1>(params_graph_up_i);

      while(j<=empty_vec.size()-1)
	{
	  empty_vec_j=empty_vec[j];
	  parameter_name=get<0>(empty_vec_j);
	  parameters_empty=get<1>(empty_vec_j);

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
  double value_update;
  string k1_i;
  string k2_i;
  string k3_i;
  string k4_i;
  double k1_i_double;
  double k2_i_double;
  double k3_i_double;
  double k4_i_double;
  string get_values_up_i;

  while(i<=k1.size()-1)
    {
      get_values_up_i=get_values_up[i];
      value_update=stod(get_values_up_i);
      k1_i=k1[i];
      k2_i=k2[i];
      k3_i=k3[i];
      k4_i=k4[i];
      k1_i_double=stod(k1_i);
      k2_i_double=stod(k2_i);
      k3_i_double=stod(k3_i);
      k4_i_double=stod(k4_i);
      result=value_update+(k1_i_double+2*k2_i_double+2*k3_i_double+k4_i_double)/6;
      result_str=to_string(result);
      rt.push_back(result_str);
      i++;
    }

  return rt;
}

void calculate()
{
  int i=0;
  int j=0;
  vector<tuple<string, tuple<vector<string>, vector<int>, vector<string>>, vector<int>, vector<string>, vector<string>>> aa;
  tuple<string, tuple<vector<string>, vector<int>, vector<string>>, vector<int>, vector<string>, vector<string>> bb;
  tuple<vector<string>, vector<int>, vector<string>> final_eq;
  vector<string> equation;
  vector<int> indices_for_ks;
  vector<string> parameter_data_for_indices;
  vector<vector<string>> equations;
  vector<vector<int>> indice_values;
  string comp_name_glob;
  vector<vector<string>> param_data;
  vector<int> calc_rules;

  cout<<"Calc"<<endl;

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

	  calc_rules=numerical_calculation_rules(equation);
	  numerical_calculation_order_of_operations.push_back(calc_rules);
	  equations.push_back(equation);
	  indice_values.push_back(indices_for_ks);
	  param_data.push_back(parameter_data_for_indices);
	  j++;
	}

      j=0;
      i++;
    }

  cout<<"Update eqs"<<endl;

  tuple<vector<vector<string>>, vector<vector<int>>, vector<vector<int>>, vector<vector<string>>> sorted1=equations_sort(equations, numerical_calculation_order_of_operations, indice_values, param_data);

  equations_sorted=get<0>(sorted1);
  numerical_calculation_order_of_operations_sorted=get<1>(sorted1);
  indice_values_sorted=get<2>(sorted1);
  param_data_sorted=get<3>(sorted1);
}

void runge_kutta()
{
  vector<string> k1;
  vector<string> k2;
  vector<string> k3;
  vector<string> k4;
  vector<string> result;
  vector<string> get_val;
  const vector<string> empty_vector={" "};
  const string zero_value="0";
  const string half_value="0.5";

  h=steps;
  double t=t_start;

  cout<<"Start calculation"<<endl;

  while(t<=t_end-h)
    {
      k1=k(equations_sorted, indice_values_sorted, empty_vector, zero_value, param_data_sorted, numerical_calculation_order_of_operations_sorted);
      k2=k(equations_sorted, indice_values_sorted, k1, half_value, param_data_sorted, numerical_calculation_order_of_operations_sorted);
      k3=k(equations_sorted, indice_values_sorted, k2, half_value, param_data_sorted, numerical_calculation_order_of_operations_sorted);
      k4=k(equations_sorted, indice_values_sorted, k3, zero_value, param_data_sorted, numerical_calculation_order_of_operations_sorted);
      get_val=get_values();
      comp=0;
      result=calculate_result(k1, k2, k3, k4, h, get_val);
      equations_sorted=update_equations(equations_sorted, indice_values_sorted, result, param_data_sorted);
      update_values(result);
      jk=0;
      t=t+h;
    }

  t=0;
  jk=0;
  comp=0;
  numerical_calculation_order_of_operations.clear();
  equations_sorted.clear();
  numerical_calculation_order_of_operations_sorted.clear();
  indice_values_sorted.clear();
  param_data_sorted.clear();
  compartment_parameters.clear();

  cout<<"Calculation ready"<<endl;
}
