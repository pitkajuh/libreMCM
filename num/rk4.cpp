/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "numerical_calculation.h"
#include "rk4_helpers.h"
#include "../class/Equations.h"
#include "../class/EquationsParseData.h"
#include "../class/Solution.h"
#include "../class/VecVecInt.h"
#include "../class/VecVecString.h"
#include "../eqs/combine_equations_and_indices.h"
#include "../math/calculate_order_of_operations.h"
#include "../math/is_operator.h"
#include "../math/is_string_numerical_value.h"
#include "../math/get_math_operator_v2.h"
#include "../util/replace_in_vector.h"
#include "../rcompartment/get_compartment_index.h"
#include "../rcompartment/get_parameter_value.h"

using std::to_string;
using std::iostream;

double t1=0;
int i_start=0;
string compartment_name_local_global="";
vector<string> global_compartment_names;

string order_of_operations(vector<string> equation, vector<int> math_op_ind)
{
  int i=0;
  int math_op_ind_i;
  int math_op_ind_ip1;
  int math_op_ind_im1;
  int indice_subtract;
  int indices_size=math_op_ind.size();
  string math_operator;
  string value1;
  string value2;
  string result;
  string eq_elem;

  while(i<=indices_size-1)
    {
      math_op_ind_i=math_op_ind[i];
      math_op_ind_ip1=math_op_ind_i+1;
      math_op_ind_im1=math_op_ind_i-1;

      math_operator=equation[math_op_ind_i];
      value1=equation[math_op_ind_im1];
      value2=equation[math_op_ind_ip1];
      result=get_math_operator2(value1, value2, math_operator);

      equation=replace_in_vector(equation, result, math_op_ind_im1, math_op_ind_ip1);
      i++;
    }
  eq_elem=equation[0];
  return eq_elem;
}

double k_subroutine(vector<string> equation, vector<int> indices, vector<string> values_to_add, string constant, VecVecString param_data, vector<int> numerical_calculation_order_of_operations)
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

vector<string> k(Equations equations, VecVecInt indices, vector<string> values_to_add, string constant, VecVecString param_data, VecVecInt numerical_calculation_order_of_operations)
{
  int i=0;
  int size=equations.get_size();
  double result;
  double result1;
  string result_str;
  vector<string> rt;
  vector<string> equation;
  vector<int> indice;
  vector<int> order_of_operation;

  while(i<=size-1)
    {
      equation=equations.get(i);
      indice=indices.get(i);
      order_of_operation=numerical_calculation_order_of_operations.get(i);

      result1=k_subroutine(equation, indice, values_to_add, constant, param_data, order_of_operation);
      result=h*result1;
      result_str=to_string(result);
      rt.push_back(result_str);
      i++;
    }
  param_data_i=0;
  return rt;
}

EquationParseData rk4_start(vector<string> equation, string compartment_name, bool add_or_not)
{
  int i=0;
  int compartment_index=get_compartment_index(compartment_name);
  int equation_size=equation.size();
  string fchar;
  string replace;
  bool is_numerical_value;
  bool is_value_operator;
  bool fchar_empty;
  vector<string> comps1;
  vector<int> indices_for_ks;
  EquationParseData result;

  while(i<=equation_size-1)
    {
      fchar=equation[i];
      is_numerical_value=is_string_numerical_value(fchar);
      is_value_operator=is_operator(fchar);
      fchar_empty=fchar.empty();

      if(!is_numerical_value and compartment_index!=-1 and !is_value_operator and !fchar_empty)
	{
	  indices_for_ks.push_back(i);
	  replace=get_compartment_parameter_value(fchar);
	  comps1.push_back(fchar);
	  equation[i]=replace;
	  equation_size=equation.size();
	}
      i++;
    }
  result.equation=equation;
  result.indices=indices_for_ks;
  result.add_equation=add_or_not, comps1;
  result.compartments=comps1;
  return result;
}

vector<Solution> solution_prepare(string compartment_name, Equations equations_add_all, Equations equations_subtract_all)
{
  int i=0;
  int j=0;
  int k=0;
  int equations_add_all_size=equations_add_all.get_size();
  int equations_subtract_all_size=equations_subtract_all.get_size();
  vector<string> equation1;
  vector<string> equation2;
  vector<string> parameter_data_for_indices;
  vector<string> multiple_last_values;
  EquationsParseData vector1;
  vector<int> indices_for_ks;
  EquationsIndicesAll equations_data;
  bool eq_add=true;
  bool eq_subtract=false;
  EquationParseData start1;
  EquationParseData start2;
  vector<Solution> data1;
  Solution data1_k;

  compartment_name_local_global=compartment_name;
  global_compartment_names.push_back(compartment_name_local_global);

  if(equations_add_all_size>0)
    {
      while(i<=equations_add_all_size-1)
	{
	  equation1=equations_add_all.get(i);
	  start1=rk4_start(equation1, compartment_name, eq_add);
	  vector1.push_back(start1);
	  i++;
	}
    }

  if(equations_subtract_all_size>0)
    {
      while(j<=equations_subtract_all_size-1)
	{
	  equation2=equations_subtract_all.get(j);
	  start2=rk4_start(equation2, compartment_name, eq_subtract);
	  vector1.push_back(start2);
	  j++;
	}
    }

  equations_data=combine_equations_and_indices(vector1, compartment_name);

  EquationsIndices final_eq1;
  int equations_data_size=equations_data.get_size();

  while(k<=equations_data_size-1)
    {
      final_eq1=equations_data.get(k);
      indices_for_ks=final_eq1.indices;
      parameter_data_for_indices=final_eq1.parameter_data;
      multiple_last_values=get_multiple_last_values(parameter_data_for_indices);

      data1_k.compartment=compartment_name;
      data1_k.final_eq1=final_eq1;
      data1_k.indices_for_ks=indices_for_ks;
      data1_k.multiple_last_values=multiple_last_values;
      data1_k.parameter_data_for_indices=parameter_data_for_indices;
      data1.push_back(data1_k);
      k++;
    }
  return data1;
}
