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
#include "helpers.h"
#include "read_bin.h"

using namespace std;

vector<string> is_variable_helper(string line)
{
  int i=0;
  vector<string> rt;
  string fchar, empty="";

  while(i<=line.size()-1)
    {
      fchar=line[i];

      if (i==line.size()-1)
	{
	  rt.push_back(fchar);
	}
      else if(is_operator(fchar))
	{
	  rt.push_back(empty);
	  rt.push_back(fchar);
	  empty="";
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
  int i=0, j=0;
  bool fchar_is_variable=false;
  vector<string> rt=is_variable_helper(fchar);

  while(i<=variables.size()-1)
    {
      if(fchar_is_variable)
	{
	  break;
	}
      while(j<=rt.size()-1)
	{
	  if(rt[j]==variables[i])
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
  return regex_match(constant, regex("^(-?)(0|([1-9][0-9]*))(\\.[0-9]+)?$"));
}

string is_number_or_constant(string ab)
{
  string parameter_value;
  bool is_number;
  is_number=is_string_numerical_value(ab);

  if(is_number or is_variable(ab))
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
  string value1=is_number_or_constant(value1_input), value2=is_number_or_constant(value2_input);
  double value1_input_double, value2_input_double;

  if(is_variable(value1_input) or is_variable(value2_input))
    {
      return value1_input+math_operator+value2_input;
    }
  else{

    value1_input_double=stod(value1_input);
    value2_input_double=stod(value2_input);

    if(math_operator==multiply)
      {
	return to_string(value1_input_double*value2_input_double);
      }
    else if(math_operator==add)
      {
	return to_string(value1_input_double+value2_input_double);
      }
    else if(math_operator==divide)
      {
	return to_string(value1_input_double/value2_input_double);
      }
    else if(math_operator==subtract)
      {
	return to_string(value1_input_double-value2_input_double);
      }
    else if(math_operator==power)
      {
	return to_string(pow(value1_input_double, value2_input_double));
      }
    else
      {
	return NULL;
      }
  }
}

vector<string> calculate_order_of_operations_helper(int index_i, int index_im1, int index_ip1, vector<string> fa)
{
  string res;

  if(is_variable(fa[index_im1]))
    {
      res=fa[index_im1]+fa[index_i]+is_number_or_constant(fa[index_ip1]);
    }
  else if(is_variable(fa[index_ip1]))
    {
      res=is_number_or_constant(fa[index_im1])+fa[index_i]+fa[index_ip1];
    }
  else
    {
      res=get_math_operator(is_number_or_constant(fa[index_im1]), is_number_or_constant(fa[index_ip1]), fa[index_i]);
    }

  fa=replace_in_vector(fa, res, index_im1, index_ip1);

  return fa;
}

vector<string> do_calc(vector<string> fa, vector<int> indices)
{
  int i=0, indice, red=2;
  vector<string> vec;

  while(i<=indices.size()-1)
    {
      if(i==0)
	{
	  indice=indices[i];
	}
      else
	{
	  indice=indices[i]-red;
	  red=red+2;
	}

      fa=calculate_order_of_operations_helper(indice, indice-1, indice+1, fa);
      i++;
  }
  return fa;
}

string calculate_order_of_operations(vector<string> fa)
{
  int i=0, j=0;
  string fchar, rt, res, calc_result;
  int fa_size=fa.size();
  vector<int> temp_vec;
  vector<string> operators={power, divide, multiply, add, subtract};

  while(i<=fa_size-1)
    {
      if(fa.size()==1)
	{
	  rt=fa[0];
	  break;
	}

      fchar=fa[i];

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
      else if(fchar==operators[j])
	{
	  temp_vec.push_back(i);
	}
      i++;
    }
  return rt;
}
