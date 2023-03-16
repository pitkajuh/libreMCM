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
#include "../global/global.h"
#include "../class/Equations.h"
#include "../class/EquationsAddSubtractParseData.h"
#include "../class/Solution.h"
#include "../class/VecVecInt.h"
#include "../class/SplittedStrings.h"
#include "../class/EquationsIndicesAll.h"
#include "../map/initial_value_map.h"
#include "../math/calculate_order_of_operations.h"
#include "../math/is_operator.h"
#include "../math/is_string_numerical_value.h"
#include "../math/get_math_operator_v2.h"
#include "../util/replace_in_vector.h"
#include "../rcompartment/get_compartment_index.h"
#include "../rcompartment/get_parameter_value.h"
#include "../debug/debug.h"

using std::to_string;

string compartment_name_local_global="";
vector<string> global_compartment_names;

string order_of_operations(vector<string> equation, const vector<int> math_op_ind)
{
  int math_op_ind_ip1;
  int math_op_ind_im1;
  string math_operator;
  string value1;
  string value2;
  string result;
  string eq_elem;

  for(const auto&i: math_op_ind)
    {
      math_op_ind_ip1=i+1;
      math_op_ind_im1=i-1;

      math_operator=equation[i];
      value1=equation[math_op_ind_im1];
      value2=equation[math_op_ind_ip1];
      result=get_math_operator2(value1, value2, math_operator);

      equation=replace_in_vector(equation, result, math_op_ind_im1, math_op_ind_ip1);
    }
  eq_elem=equation[0];
  return eq_elem;
}

double k_subroutine(vector<string> equation, const vector<int> indices, vector<string> values_to_add, const string constant, const SplittedStrings param_data, const vector<int> numerical_calculation_order_of_operations)
{
  int i=0;
  double result;
  string result_str;
  const int size=values_to_add.size();

  if(size>1)
    {
      values_to_add=values_to_add_update(values_to_add, constant);
      equation=replace_in_whole_equation(equation, indices, values_to_add, param_data);
    }

  result_str=order_of_operations(equation, numerical_calculation_order_of_operations);
  result=stod(result_str);
  return result;
}

vector<string> k(Equations equations, const VecVecInt indices, const vector<string> values_to_add, const string constant, const SplittedStrings param_data, const VecVecInt numerical_calculation_order_of_operations)
{
  int i=0;
  const int size=equations.size();
  double result;
  double result1;
  string result_str;
  vector<string> rt;
  vector<string> equation;
  vector<int> indice;
  vector<int> order_of_operation;

  while(i<=size-1)
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
  param_data_i=0;
  return rt;
}

EquationParseData eq_get_param_value(vector<string> equation, const string compartment_name)
{
  int i=0;
  const int compartment_index=get_compartment_index(compartment_name);
  const int equation_size=equation.size();
  string fchar;
  string replace;
  bool is_numerical_value;
  bool is_value_operator;
  bool fchar_empty;
  vector<SplittedString> comps1;
  SplittedString splitted;
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
	  splitted=initial_value_map[fchar];
	  comps1.push_back(splitted);
	  equation[i]=replace;
	}
      i++;
    }
  result.equation=equation;
  result.indices=indices_for_ks;
  result.compartments=comps1;
  return result;
}

vector<string> equation_subtract_func(vector<string> fa)
{
  // Changes minus signs to plus signs in an equation.
  int i=0;
  int ip1;
  const int size=fa.size();
  const int zero_value=0;
  string fchar;
  string fchar_ip1;

  while(i<=size-1)
    {
      fchar=fa[i];
      fchar_ip1=fchar[0];

      if(i==0)
	{
	  if(fchar_ip1==SUBTRACT)
	    {
	      fchar.erase(fchar.begin()+zero_value);
	      fa[i]=fchar;
	    }
	  else
	    {
	      fa[i]=SUBTRACT+fchar;
	    }
	}

      if(fchar_ip1==SUBTRACT and i>0)
	{
	  fchar.erase(fchar.begin()+zero_value);
	  fa[i]=fchar;
	}
      i++;
    }
  return fa;
}

EquationsIndicesAll combine(Equations equations_add_all, Equations equations_subtract_all, const string compartment_name)
{
  int i=0;
  const int equations_add_all_size=equations_add_all.size();
  const int equations_subtract_all_size=equations_subtract_all.size();
  vector<string> equation_total;
  vector<string> equation_add;
  vector<string> equation_subtract;
  vector<int> indices;
  EquationsParseData rt;
  EquationParseData data;
  EquationsIndicesAll data_all;
  EquationsIndices data1;

  if(equations_add_all_size==equations_subtract_all_size)
    {
      while(i<=equations_add_all_size-1)
	{
	  equation_add=equations_add_all[i];
	  equation_subtract=equations_subtract_all[i];
	  equation_subtract=equation_subtract_func(equation_subtract);
	  equation_add.push_back(ADD);
	  equation_total=combine_vectors(equation_subtract, equation_add);

	  data=eq_get_param_value(equation_total, compartment_name);
	  data1.equation=data.equation;
	  data1.indices=data.indices;
	  data1.parameter_data=data.compartments;
	  data_all.push_back(data1);
	  rt.push_back(data);
	  i++;
	}
    }
  else if(equations_add_all_size>0 and equations_subtract_all_size==0)
    {
      while(i<=equations_add_all_size-1)
	{
	  equation_total=equations_add_all[i];
	  data=eq_get_param_value(equation_total, compartment_name);
	  data1.equation=data.equation;
	  data1.indices=data.indices;
	  data1.parameter_data=data.compartments;
	  data_all.push_back(data1);
	  rt.push_back(data);
	  i++;
	}
    }
  else if(equations_add_all_size==0 and equations_subtract_all_size>0)
    {
      while(i<=equations_subtract_all_size-1)
	{
	  equation_total=equations_subtract_all[i];
	  data=eq_get_param_value(equation_total, compartment_name);
	  data1.equation=data.equation;
	  data1.indices=data.indices;
	  data1.parameter_data=data.compartments;
	  data_all.push_back(data1);
	  rt.push_back(data);
	  i++;
	}
    }
  return data_all;
}

vector<Solution> solution_prepare(const string compartment_name, Equations equations_add_all, Equations equations_subtract_all)
{
  int i=0;
  vector<SplittedString> parameter_data_for_indices;
  vector<string> multiple_last_values;
  vector<string> equation_total;
  vector<int> indices_for_ks;
  vector<Solution> data1;
  Solution data1_i;
  EquationsAddSubtractParseData equations_add_subtract;
  EquationsIndicesAll equations_data=combine(equations_add_all, equations_subtract_all, compartment_name);
  const int equations_data_size=equations_data.size();
  EquationsIndices final_eq1;

  compartment_name_local_global=compartment_name;
  global_compartment_names.push_back(compartment_name_local_global);

  while(i<=equations_data_size-1)
    {
      final_eq1=equations_data[i];
      indices_for_ks=final_eq1.indices;
      parameter_data_for_indices=final_eq1.parameter_data;

      multiple_last_values=get_multiple_last_values(parameter_data_for_indices);

      data1_i.compartment=compartment_name;
      data1_i.final_eq1=final_eq1;
      data1_i.indices_for_ks=indices_for_ks;
      data1_i.multiple_last_values=multiple_last_values;
      data1_i.parameter_data_for_indices=parameter_data_for_indices;

      data1.push_back(data1_i);
      i++;
    }
  return data1;
}
