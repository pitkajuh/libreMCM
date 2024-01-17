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
#include "../class/K_vec.h"
#include "../global/h.h"
#include "../global/odes.h"
#include "../math/get_math_operator.h"

using std::to_string;

const string order_of_operations(vector<string> equation, const vector<int> indices)
{
  int i_p;
  int i_m;
  string math_operator;

  for(const auto&i: indices)
    {
      i_p=i+1;
      i_m=i-1;
      math_operator=equation[i];
      equation[i_p]=get_math_operator2(equation[i_m], equation[i_p], math_operator);
      equation.erase(equation.begin()+i_m, equation.begin()+i_p);
    }
  return equation[0];
}

const vector<string> values_to_add_update(vector<double> values_to_add, const double constant)
{
  int j=0;
  vector<string> result;

  if(constant!=0)
    {
      for(auto const&i: values_to_add)
	{
	  result.push_back(to_string(constant*i));
	  j++;
	}
    }
  else
    {
      for(auto const&i: values_to_add)
	{
	  result.push_back(to_string(i));
	  j++;
	}
    }
  return result;
}

const double k_subroutine(vector<string> equation, const vector<int> indices, vector<double> values_to_add, const double constant, const vector<int> math_op_indices, const int indice)
{
  const vector<string> replace_value=values_to_add_update(values_to_add, constant);
  equation=replace_in_whole_equation(equation, indices, replace_value, param_data, indice);
  const double result=stod(order_of_operations(equation, math_op_indices));
  return result;
}

const vector<double> k0()
{
  int i=0;
  const int size=equations.size()-1;
  double result;
  vector<int> indice;
  vector<int> order_of_operation;
  vector<double> rt;
  vector<string> equation;

  while(i<=size)
    {
      equation=equations[i];
      indice=indice_values[i];
      order_of_operation=math_op_indices[i];
      result=h*stod(order_of_operations(equation, order_of_operation));
      rt.push_back(result);
      i++;
    }
  return rt;
}

const vector<double> k(K_vec values_to_add, const double constant)
{
  int i=0;
  const int size=equations.size()-1;
  double result;
  vector<int> indice;
  vector<int> order_of_operation;
  vector<double> rt;
  vector<string> equation;

  while(i<=size)
    {
      equation=equations[i];
      indice=indice_values[i];
      order_of_operation=math_op_indices[i];
      result=h*k_subroutine(equation, indice, values_to_add.t1, constant, order_of_operation, i);
      rt.push_back(result);
      i++;
    }
  return rt;
}
