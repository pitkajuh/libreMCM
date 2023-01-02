/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <cmath>
#include <regex>
#include "global.h"
#include "replace_in_vector.h"
#include "is_operator.h"
#include "read_bin.h"

using namespace std;

vector<string> is_variable_helper(string line)
{
  int i=0;
  const string empty_str="";
  vector<string> rt;
  string fchar;
  string empty=empty_str;
  bool is_operator_or_not;

  while(i<=line.size()-1)
    {
      fchar=line[i];
      is_operator_or_not=is_operator(fchar);

      if(i==line.size()-1)
	{
	  rt.push_back(fchar);
	}
      else if(is_operator_or_not)
	{
	  rt.push_back(empty);
	  rt.push_back(fchar);
	  empty=empty_str;
	  i++;
	  continue;
	}
      else
	{
	  empty=empty+fchar;
	}
      i++;
    }
  return rt;
}

bool is_variable(string fchar)
{
  int i=0;
  int j=0;
  bool fchar_is_variable=false;
  vector<string> rt=is_variable_helper(fchar);
  string rt_j;
  string variables_i;

  while(i<=variables.size()-1)
    {
      if(fchar_is_variable)
	{
	  break;
	}
      while(j<=rt.size()-1)
	{
	  rt_j=rt[j];
	  variables_i=variables[i];

	  if(rt_j==variables_i)
	    {
	      fchar_is_variable=true;
	      break;
	    }
	  j++;
	}
      j=0;
      i++;
    }

  return fchar_is_variable;
}

bool is_string_numerical_value(string constant)
{
  // Checks whether there are numbers(0-9) in the equations, not only constants and variables. Returns true, if string is a valid number.

  bool result=regex_match(constant, regex("^(-?)(0|([1-9][0-9]*))(\\.[0-9]+)?$"));

  return result;
}

string is_number_or_constant(string ab)
{
  string parameter_value;
  bool is_number=is_string_numerical_value(ab);
  bool is_str_variable=is_variable(ab);

  if(is_number or is_str_variable)
    {
      parameter_value=ab;
    }
  else
    {
      parameter_value=get_constant_value(ab);
    }

  return parameter_value;
}

string get_math_operator(string value1_input, string value2_input, string math_operator)
{
  double value1_input_double;
  double value2_input_double;
  string result;
  double result_double;
  bool is_value1_variable=is_variable(value1_input);
  bool is_value2_variable=is_variable(value2_input);

  if(is_value1_variable or is_value2_variable)
    {
      result=value1_input+math_operator+value2_input;
    }
  else
    {
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
    }

  result=to_string(result_double);
  return result;
}

vector<string> calculate_order_of_operations_helper(int index_i, int index_im1, int index_ip1, vector<string> fa)
{
  string res;
  string fa_im1=fa[index_im1];
  string fa_ip1=fa[index_ip1];
  string fa_i=fa[index_i];
  string number_or_const_ip1;
  string number_or_const_im1;
  bool is_variable_im1=is_variable(fa_im1);
  bool is_variable_ip1;

  if(!is_variable_im1)
    {
      is_variable_ip1=is_variable(fa_ip1);
    }



  if(is_variable_im1)
    {
      number_or_const_ip1=is_number_or_constant(fa_ip1);
      res=fa_im1+fa_i+number_or_const_ip1;
    }
  else if(is_variable_ip1)
    {
      number_or_const_im1=is_number_or_constant(fa_im1);
      res=number_or_const_im1+fa_i+fa_ip1;
    }
  else
    {
      number_or_const_ip1=is_number_or_constant(fa_ip1);
      number_or_const_im1=is_number_or_constant(fa_im1);
      res=get_math_operator(number_or_const_im1, number_or_const_ip1, fa_i);
    }

  fa=replace_in_vector(fa, res, index_im1, index_ip1);
  return fa;
}

vector<string> do_calc(vector<string> fa, vector<int> indices)
{
  int i=0;
  int indice;
  int fchar;
  const int value_add=2;
  int red=value_add;
  vector<string> vec;

  while(i<=indices.size()-1)
    {
      fchar=indices[i];

      if(i==0)
	{
	  indice=fchar;
	}
      else
	{
	  indice=fchar-red;
	  red=red+value_add;
	}

      fa=calculate_order_of_operations_helper(indice, indice-1, indice+1, fa);
      i++;
  }

  return fa;
}

string calculate_order_of_operations(vector<string> fa)
{
  int i=0;
  int j=0;
  string fchar;
  string rt;
  string res;
  string calc_result;
  int fa_size=fa.size();
  vector<int> temp_vec;
  vector<string> operators={power, divide, multiply, add, subtract};
  string operators_i;

  while(i<=fa_size-1)
    {
      if(fa.size()==1)
	{
	  rt=fa[0];
	  break;
	}

      fchar=fa[i];
      operators_i=operators[j];

      if(temp_vec.size()==0 and i==fa.size()-1)
	{
	  j++;
	  i=0;
	  continue;
	}
      else if(temp_vec.size()>0 and i==fa.size()-1)
	{
	  fa=do_calc(fa, temp_vec);
	  fa_size=fa.size();
	  temp_vec.clear();

	  if(j==operators.size()-1)
	    {
	      rt=fa[0];
	      break;
	    }
	  else
	    {
	      j++;
	      i=0;
	      continue;
	    }
	}
      else if(fchar==operators_i)
	{
	  temp_vec.push_back(i);
	}
      i++;
    }

  return rt;
}
