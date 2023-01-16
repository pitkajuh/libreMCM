/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "global.h"
#include "is_operator.h"
#include "read_config_sub.h"
#include "calculate_order_of_operations.h"

using namespace std;

vector<string> variables;
vector<tuple<string, string>> func_params;

vector<string> get_elem(vector<string> fa, int start, int stop)
{
  int i=start;
  string emp="";
  string fchar;
  vector<string> rt;

  while(i<=stop)
    {
      fchar=fa[i];
      rt.push_back(fchar);
      emp=emp+fchar;
      i++;
    }
  return rt;
}

string calculate_equation_constants(vector<string> fa)
{
  /*
    Calculates an equation according to order of operations:

    1. Parentheses
    2. Exponents
    3. Multiplication and division
    4. Addition and subtraction
  */

  return calculate_order_of_operations(fa);
}

string equation_read(string func_name, string func_value)
{
  int i=0;
  int last_operator_index;
  vector<string> fa;
  const string empty_str="";
  string abb=empty_str;
  string fchar;
  string read_bin_result;
  bool is_str_operator;
  string sub_string;

  while(i<=func_value.size()-1)
    {
      fchar=func_value[i];
      is_str_operator=is_operator(fchar);

      if(is_str_operator and i==0)
	{
	  fa.push_back(fchar);
	}
      else if(is_str_operator)
	{
	  if(abb.length()>0)
	    {
	      fa.push_back(abb);
	      abb=empty_str;
	    }
	  fa.push_back(fchar);
	  last_operator_index=i;
	}
      else
	{
	  abb=abb+fchar;
	}
      i++;
    }

  if(last_operator_index!=func_value.size()-1)
    {
      sub_string=func_value.substr(last_operator_index+1, func_value.size()-1-last_operator_index);
      fa.push_back(sub_string);
    }

  read_bin_result=calculate_equation_constants(fa);
  return read_bin_result;
}

tuple<string, string> read_equations(string line)
{
  int i=0;
  string fchar;
  string ab;
  string empty_str="";
  string equation_name;
  string equation_value;
  bool eq_found=false;
  tuple<string, string> rt;
  const string empty1=" ";
  const string empty2="\0";

  while(i<=line.size()-1)
  {
    fchar=line[i];

      if(fchar==delimiter)
	{
	  equation_value=ab;
	}
      else if(fchar==empty2 or fchar==empty1 or fchar.empty())
	{
	  i++;
	  continue;
	}
      else if(fchar==equal_sign)
	{
	  equation_name=ab;
	  ab=empty_str;
	  eq_found=true;
	}
      else
	{
	  ab=ab+fchar;
	}
      i++;
    }

  rt=make_tuple(equation_name, equation_read(equation_name, equation_value));
  return rt;
}

string get_variable(string line)
{
  int i=0;
  string fchar;
  string variable;
  string ab;
  const string empty1=" ";
  const string empty2="\0";

  while(i<=line.size()-1)
    {
      fchar=line[i];

      if(fchar==delimiter)
	{
	  variable=ab;
	  break;
	}
      else if(fchar==empty2 or fchar==empty1 or fchar.empty())
	{
	  i++;
	  continue;
	}
      else
	{
	  ab=ab+fchar;
	}
      i++;
    }

  return variable;
}

vector<tuple<string, string>> read_bin()
{
  const string file_name="cfg/bin";
  fstream bin_loaded(file_name, ios_base::in | ios::binary);
  string line;
  bool constants_found=false;
  bool equations_found=false;
  bool variables_found=false;
  bool constants_saved=false;
  bool equations_saved=false;
  bool variables_saved=false;
  vector<tuple<string, string>> rt;
  const string constants_str="constants";
  const string equations_str="equations";
  const string variables_str="variables";
  tuple<string, string> read_constants_result;
  tuple<string, string> read_equations_result;
  string get_variable_result;
  string line_commented;

  while(getline(bin_loaded, line))
    {
      line_commented=line_commented_or_not(line);

      if(line.empty() or line_commented.empty())
	{
	  continue;
	}
      else if(!variables_saved)
	{
	  if(line==curly_bracket_c and variables_found)
	    {
	      variables_saved=true;
	      continue;
	    }
	  else if(line==variables_str or line==variables_str+curly_bracket_o)
	    {
	      variables_found=true;
	      continue;
	    }
	  else if(variables_found)
	    {
	      get_variable_result=get_variable(line);
	      variables.push_back(get_variable_result);
	    }
	}
      else if(!constants_saved)
	{
	  if(line==curly_bracket_c and constants_found)
	    {
	      constants_saved=true;
	      continue;
	    }
	  else if(line==constants_str or line==constants_str+curly_bracket_o)
	    {
	      constants_found=true;
	      continue;
	    }
	  else if(constants_found)
	    {
	      read_constants_result=read_constants(line);
	      func_params.push_back(read_constants_result);
	    }
	}
      else if(!equations_saved)
	{
	  if(line==curly_bracket_c and equations_found)
	    {
	      constants_saved=true;
	      continue;
	    }
	  else if(line==equations_str or line==equations_str+curly_bracket_o)
	    {
	      equations_found=true;
	      continue;
	    }
	  else if(equations_found)
	    {
	      read_equations_result=read_equations(line);
	      rt.push_back(read_equations_result);
	    }
	}
    }

  return rt;
}

string get_constant_value(string constant)
{
  int i=0;
  bool value_found=false;
  string value_found_return;
  double value_found_return_double;
  string compare;
  tuple<string, string> func_params_i;

  while(i<=func_params.size()-1)
    {
      func_params_i=func_params[i];
      compare=get<0>(func_params_i);

      if(constant==compare)
	{
	  value_found=true;
	  value_found_return=get<1>(func_params_i);
	  value_found_return_double=stod(value_found_return);
	  value_found_return=to_string(value_found_return_double);
	  break;
	}
      i++;
    }
  if(value_found)
    {
      return value_found_return;
    }
  else
    {
      return NULL;
    }
}

vector<tuple<string, string>> get_equations()
{
  int i=0;
  vector<tuple<string, string>> result=read_bin();
  return result;
}

vector<tuple<string, string>> equations=get_equations();
