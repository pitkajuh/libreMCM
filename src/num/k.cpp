/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "rk4_helpers.h"
#include "../class/VecVecInt.h"
#include "../class/SplittedStrings.h"
#include "../class/Equations.h"
#include "../global/h.h"
#include "../global/odes.h"
#include "../math/get_math_operator.h"

using std::to_string;

const string order_of_operations(vector<string> equation, const vector<int> indices)
{
  int indices_ip1;
  int indices_im1;
  string math_operator;
  string value1;
  string value2;
  string result;
  string eq_elem;

  for(const auto&i: indices)
    {
      indices_ip1=i+1;
      indices_im1=i-1;
      math_operator=equation[i];
      value1=equation[indices_im1];
      value2=equation[indices_ip1];
      result=get_math_operator2(value1, value2, math_operator);

      equation[indices_ip1]=result;
      equation.erase(equation.begin()+indices_im1, equation.begin()+indices_ip1);
    }
  eq_elem=equation[0];
  return eq_elem;
}

const vector<string> values_to_add_update(vector<double> values_to_add, const double constant)
{
  int j=0;
  double result;
  string result_str;
  vector<string> result1;

  if(constant!=0)
    {
      for(auto const&i: values_to_add)
	{
	  result=constant*i;
	  result_str=to_string(result);
	  result1.push_back(result_str);
	  j++;
	}
    }
  else
    {
      for(auto const&i: values_to_add)
	{
	  result_str=to_string(i);
	  result1.push_back(result_str);
	  j++;
	}
    }
  return result1;
}

const double k_subroutine(vector<string> equation, const vector<int> indices, vector<double> values_to_add, const double constant, const vector<int> math_op_indices, const int indice)
{
  int i=0;
  double result;
  string result_str;
  const int size=values_to_add.size();
  vector<string> replace_value;

  if(size>1)
    {
      replace_value=values_to_add_update(values_to_add, constant);
      equation=replace_in_whole_equation(equation, indices, replace_value, param_data, indice);
    }
  result_str=order_of_operations(equation, math_op_indices);
  result=stod(result_str);
  return result;
}

const vector<double> k(const vector<double> values_to_add, const double constant)
{
  int i=0;
  const int size=equations.size()-1;
  double result;
  string result_str;
  vector<int> indice;
  vector<int> order_of_operation;
  vector<double> rt;
  vector<string> equation;

  while(i<=size)
    {
      equation=equations[i];
      indice=indice_values[i];
      order_of_operation=math_op_indices[i];
      result=h*k_subroutine(equation, indice, values_to_add, constant, order_of_operation, i);
      rt.push_back(result);
      i++;
    }
  return rt;
}
