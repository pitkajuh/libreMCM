/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "combine_equations_and_indices.h"
#include "numerical_calculation.h"
#include "rk4_helpers.h"
#include "calculate_order_of_operations.h"
#include "replace_in_vector.h"
#include "is_operator.h"
#include "string_split.h"
#include "get_compartment_equations.h"
#include "helpers.h"

using namespace std;

double t1=0;

vector<string> vector_add;
vector<string> vector_subtract;
int i_start=0;
string compartment_name_local_global;
vector<string> global_compartment_names;

string get_math_operator2(string value1_input, string value2_input, string math_operator)
{
  double value1_input_double;
  double value2_input_double;
  string result;
  double result_double;

  value1_input_double=stod(value1_input);
  value2_input_double=stod(value2_input);

  if(math_operator==multiply)
    {
      result_double=value1_input_double*value2_input_double;
    }
  else if(math_operator==add)
    {
      result_double=value1_input_double+value2_input_double;
    }
  else if(math_operator==divide)
    {
      result_double=value1_input_double/value2_input_double;
    }
  else if(math_operator==subtract)
    {
      result_double=value1_input_double-value2_input_double;
    }
  else if(math_operator==power)
    {
      result_double=pow(value1_input_double, value2_input_double);
    }

  result=to_string(result_double);
  return result;
}

vector<int> indices_update2(vector<int> indices, int nr, int i_from)
{
  int i=i_from;
  int indice;

  while(i<=indices.size()-1)
    {
      indice=indices[i];

      if(indice!=1)
	{
	  indices[i]=indice-nr;
	}
      i++;
    }

  return indices;
}

string order_of_operations(vector<string> equation, vector<int> math_op_ind)
{
  int i=0;
  const int i_from=0;
  string math_operator;
  string value1;
  string value2;
  string result;
  int math_op_ind_i;
  int math_op_ind_ip1;
  int math_op_ind_im1;
  string eq_elem;

  while(i<=math_op_ind.size()-1)
    {
      if(equation.size()==1)
	{
	  break;
	}

      math_op_ind_i=math_op_ind[i];
      math_op_ind_ip1=math_op_ind_i+1;
      math_op_ind_im1=math_op_ind_i-1;

      math_operator=equation[math_op_ind_i];
      value1=equation[math_op_ind_im1];
      value2=equation[math_op_ind_ip1];
      result=get_math_operator2(value1, value2, math_operator);
      equation=replace_in_vector(equation, result, math_op_ind_im1, math_op_ind_ip1);
      math_op_ind=indices_update2(math_op_ind, 2, i_from);
      i++;
    }

  eq_elem=equation[0];
  return eq_elem;
}

double k_subroutine(vector<string> equation, vector<int> indices, vector<string> values_to_add, string constant, vector<vector<string>> param_data, vector<int> numerical_calculation_order_of_operations)
{
  int i=0;
  double result;
  string result_str;

  if(values_to_add.size()>1)
    {
      values_to_add=values_to_add_update(values_to_add, constant);
      equation=replace_in_whole_equation(equation, indices, values_to_add, constant, param_data);
    }

  result_str=order_of_operations(equation, numerical_calculation_order_of_operations);
  result=stod(result_str);
  return result;
}

vector<string> k(vector<vector<string>> equations, vector<vector<int>> indices, vector<string> values_to_add, string constant, vector<vector<string>> param_data, vector<vector<int>> numerical_calculation_order_of_operations)
{
  int i=0;
  double result;
  double result1;
  vector<string> rt;
  vector<string> equation;
  vector<int> indice;
  vector<int> order_of_operation;
  string result_str;

  while(i<=equations.size()-1)
    {
      equation=equations[i];
      indice=indices[i];
      order_of_operation=numerical_calculation_order_of_operations[i];

      result1=k_subroutine(equation, indice, values_to_add, constant, param_data, order_of_operation);
      result=h*result1;
      result_str=to_string(result);
      rt.push_back(result_str);
      i++;
    }

  asd=0;
  return rt;
}

tuple<vector<string>, vector<int>, bool, vector<string>>
rk4_start(vector<string> equation, string compartment_name, bool add_or_not)
{
  int i=0;
  int j=0;
  string fchar;
  string replace;
  string subtract_from_compartment;
  string add_to_compartment;
  int equation_size=equation.size();
  tuple<vector<string>, int> target_compartments_all;
  vector<string> target_compartments;
  vector<string> comps1;
  vector<int> indices_for_ks;
  tuple<string, string> param1;
  string target_compartments_j;
  tuple<vector<string>, vector<int>, bool, vector<string>> result;
  bool is_numerical_value;
  int compartment_index;
  bool is_value_operator;

  while(i<=equation_size-1)
    {
      fchar=equation[i];
      is_numerical_value=is_string_numerical_value(fchar);
      compartment_index=get_compartment_index(compartment_name);
      is_value_operator=is_operator(fchar);

      if(!is_numerical_value and compartment_index!=-1 and !is_value_operator)
	{
	  target_compartments_all=get_target_compartments(compartment_name, add_or_not, i_start);
	  target_compartments=get<0>(target_compartments_all);
	  i_start=get<1>(target_compartments_all);

	  while(j<=target_compartments.size()-1)
	    {
	      target_compartments_j=target_compartments_j;

	      if(target_compartments_j==origin_element and !add_or_not)
		{
		  subtract_from_compartment=target_compartments_j;
		  add_to_compartment=compartment_name;
		}
	      else
		{
		  subtract_from_compartment=target_compartments_j;
		  add_to_compartment=compartment_name;
		}
	      j++;
	    }

	  j=0;
	  param1=split_string_in_two(fchar, parm_delim);
	  indices_for_ks.push_back(i);
	  replace=get_compartment_parameter_value(fchar);
	  comps1.push_back(fchar);
	  equation=replace_in_vector(equation, replace, i, i);
	  equation_size=equation.size();
	}
      i++;
    }

  result=make_tuple(equation, indices_for_ks, add_or_not, comps1);
  return result;
}

vector<tuple<string, tuple<vector<string>, vector<int>, vector<string>>, vector<int>, vector<string>, vector<string>>>
solution_prepare(string compartment_name, vector<vector<string>> equations_add_all, vector<vector<string>> equations_subtract_all)
{
  int i=0;
  int j=0;
  int k=0;
  vector<string> equation1;
  vector<string> equation2;
  vector<string> equation;
  vector<string> parameter_data_for_indices;
  vector<string> multiple_last_values;
  vector<string> final_eq;
  vector<tuple<vector<string>, vector<int>, bool, vector<string>>> vector1;
  vector<int> indices_for_ks;
  vector<tuple<vector<string>, vector<int>, vector<string>>> equations_data;

  tuple<vector<string>, vector<int>, bool, vector<string>> start1;
  tuple<vector<string>, vector<int>, bool, vector<string>> start2;
  vector<
    tuple<string, // compartment_name
       tuple<vector<string>, vector<int>, vector<string>>, //final_eq
       vector<int>, // indices_for_ks
       vector<string>, // multiple_last_values
       vector<string> // parameter_data_for_indices
       >
    > data1;

    tuple<string, // compartment_name
       tuple<vector<string>, vector<int>, vector<string>>, //final_eq
       vector<int>, // indices_for_ks
       vector<string>, // multiple_last_values
       vector<string> // parameter_data_for_indices
       > data1_k;

  compartment_name_local_global=compartment_name;
  global_compartment_names.push_back(compartment_name_local_global);

  if(equations_add_all.size()>=1)
    {
      while(i<=equations_add_all.size()-1)
	{
	  equation1=equations_add_all[i];
	  start1=rk4_start(equation1, compartment_name, true);
	  vector1.push_back(start1);
	  i++;
	}
    }



  if(equations_subtract_all.size()>=1)
    {
      while(j<=equations_subtract_all.size()-1)
	{
	  equation2=equations_subtract_all[j];
	  start2=rk4_start(equation2, compartment_name, false);
	  vector1.push_back(start2);
	  j++;
	}
    }

  equations_data=combine_equations_and_indices(vector1, compartment_name);

  tuple<vector<string>, vector<int>, vector<string>> final_eq1;

  // vector<string> test;

  while(k<=equations_data.size()-1)
    {
      // cout<<"k "<<k<<"/"<<equations_data.size()-1<<endl;
      final_eq1=equations_data[k];

      // test=get<0>(final_eq1);
      // print_vector(test);

      indices_for_ks=get<1>(final_eq1);
      parameter_data_for_indices=get<2>(final_eq1);
      multiple_last_values=get_multiple_last_values(parameter_data_for_indices);

      // cout<<"multiple_last_values"<<endl;

      data1_k=make_tuple(compartment_name, final_eq1, indices_for_ks, multiple_last_values, parameter_data_for_indices);
      data1.push_back(data1_k);
      k++;
    }

  // cout<<"solution_prepare ok"<<endl;

  return data1;
}
