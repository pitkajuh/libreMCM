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
#include "is_operator.h"
#include "../global/global.h"
#include "../rcfg/read_bin.h"
#include "../util/replace_in_vector.h"
#include "../util/vector_convert.h"
#include "../util/vector_split.h"

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

  string str="^(-?)(0|([1-9][0-9]*))(\\.[0-9]+)?$";
  bool result=regex_match(constant, regex(str));

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
      double value1_input_double=value1_input_double=stod(value1_input);
      double value2_input_double=value2_input_double=stod(value2_input);

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

vector<string> do_calculation(vector<string> fa, int index)
{
  int im1=index-1;
  int ip1=index+1;
  int im2=index-2;
  int ip2=index+2;
  int im3=index-3;
  int ip3=index+3;
  string math_operator=fa[index];
  string fa_im1=fa[im1];
  string fa_ip1=fa[ip1];
  string fa_im2;
  string fa_ip2;
  string fa_im3;
  string fa_ip3;
  string result;
  string rt;
  bool fa_im1_var=is_variable(fa_im1);
  bool fa_ip1_var=is_variable(fa_ip1);

  if(fa_ip1_var)
    {
      fa_im1=is_number_or_constant(fa_im1);
      result=fa_im1;
      ip1=im1;
      fa=replace_in_vector(fa, result, im1, ip1);
    }
  else if(fa_im1_var)
    {
      fa_ip1=is_number_or_constant(fa_ip1);
      result=fa_ip1;
      im1=ip1;
      fa=replace_in_vector(fa, result, im1, ip1);
    }
  else if(fa_ip1==open_parenthesis)
    {
      fa_im1=is_number_or_constant(fa_im1);
      result=fa_im1;
      ip1=im1;
      fa=replace_in_vector(fa, result, im1, ip1);
    }
  else if(fa_im1==open_parenthesis or fa_ip1==close_parenthesis or fa_im1==close_parenthesis or fa_ip1==open_parenthesis)
    {
      return fa;
    }
  else if(!fa_ip1_var and !fa_im1_var)
    {
      fa_im1=is_number_or_constant(fa_im1);
      fa_ip1=is_number_or_constant(fa_ip1);

      if(ip2<=fa.size()-1 and ip3<=fa.size()-1)
	{
	  fa_ip2=fa[ip2];
	  fa_ip3=fa[ip3];
	  bool is_value_variable=is_variable(fa_ip3);

	  if(fa_ip3==open_parenthesis and fa_ip2==multiply or fa_ip2==divide)
	    {
	      if(math_operator==add or math_operator==subtract)
		{
		  return fa;
		}
	    }
	  else if(math_operator==add or math_operator==subtract and fa_ip2==multiply or fa_ip2==divide)
	    {
	      if(is_value_variable)
		{
		  return fa;
		}
	    }
	}

      if(im2>=0 and im3>=0)
	{
	  fa_im2=fa[im2];
	  fa_im3=fa[im3];

	  if(fa_im3==close_parenthesis and fa_im2==multiply or fa_im2==divide)
	    {
	      if(math_operator==add or math_operator==subtract)
		{
		  result=fa_im1;
		  fa=replace_in_vector(fa, result, im1, im1);
		  return fa;
		}
	    }
	  else if(fa_im2==subtract and math_operator==subtract)
	    {
	      fa_im1=fa_im2+fa_im1;
	      result=get_math_operator(fa_im1, fa_ip1, math_operator);
	      im1=im1-1;
	      fa=replace_in_vector(fa, result, im1, ip1);
	      return fa;
	    }
	}

      result=get_math_operator(fa_im1, fa_ip1, math_operator);
      fa=replace_in_vector(fa, result, im1, ip1);
    }

  return fa;
}

vector<string> calculate_order_of_operations2(vector<string> fa)
{
  int i=0;
  int j=0;
  string fchar;
  string res;
  string calc_result;
  int fa_size=fa.size();
  int fa_size_prev;
  vector<int> indices;
  const vector<string> operators={power, multiply, divide, add, subtract};
  string operators_i;

  while(j<=operators.size()-1)
    {
      if(i>fa_size-1)
	{
	  i=0;
	  continue;
	}

      fchar=fa[i];
      operators_i=operators[j];

      if(i==fa_size-1)
	{
	  j++;
	  i=0;
	  fa_size=fa.size();
	  continue;
	}


      if(fchar==operators_i)
	{
	  fa_size_prev=fa.size();
	  fa=do_calculation(fa, i);
	  fa_size=fa.size();
	  i=i-fa_size_prev+fa_size;
	}

      i++;
    }

  return fa;
}
