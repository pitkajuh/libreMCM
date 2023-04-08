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
#include "../math/get_math_operator_v2.h"

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

const double k_subroutine(vector<string> equation, const vector<int> indices, vector<string> values_to_add, const string constant, SplittedStrings param_data, const vector<int> numerical_calculation_order_of_operations, const int indice)
{
  int i=0;
  double result;
  string result_str;
  const int size=values_to_add.size();

  if(size>1)
    {
      values_to_add=values_to_add_update(values_to_add, constant);
      equation=replace_in_whole_equation(equation, indices, values_to_add, param_data, indice);
    }
  result_str=order_of_operations(equation, numerical_calculation_order_of_operations);
  result=stod(result_str);
  return result;
}

const vector<string> k(Equations equations, const VecVecInt indices, const vector<string> values_to_add, const string constant, const SplittedStrings param_data, const VecVecInt numerical_calculation_order_of_operations)
{
  int i=0;
  const int size=equations.size()-1;
  double result;
  string result_str;
  vector<int> indice;
  vector<int> order_of_operation;
  vector<string> rt;
  vector<string> equation;

  while(i<=size)
    {
      equation=equations[i];
      indice=indices[i];
      order_of_operation=numerical_calculation_order_of_operations[i];

      result=h*k_subroutine(equation, indice, values_to_add, constant, param_data, order_of_operation, i);
      result_str=to_string(result);
      rt.push_back(result_str);
      i++;
    }
  return rt;
}
