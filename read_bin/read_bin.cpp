/*
  Created: 22.04.2022 18:35

  Author: pitkajuh
*/

/*
Gets from the constants section from bin file and calculates the equations as described in the equations section of the bin file.
*/

#include <iostream>
#include <stdlib.h>
#include <tuple>
#include <cmath>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <assert.h>
#include <regex>
#include "global.h"
#include "helpers.h"

using namespace std;

vector<string> variables;
vector<tuple<string, double>> func_params;
string constants_str="constants", equations_str="equations", variables_str="variables", curly_bracket_o="{", curly_bracket_c="}";

vector<string> get_elem(vector<string> fa, int start, int stop)
{
  int i=start;
  string emp="";
  vector<string> rt;
  while(i<=stop)
    {
      rt.push_back(fa[i]);
      emp=emp+fa[i];
      // cout<<fa[i]<<" "<<emp<<endl;
      i++;
    }
  // cout<<"get_elem "<<emp<<endl;
  return rt;
}

string calculate_order_of_operations(vector<string> fa, int size)
{
  int i=0;
  bool no_exponents=false, no_division=false, no_multiplication=false, no_addition=false, no_subtraction=false;
  string fchar, rt;
  double calc_result;

  while(i<=size)
    {
      fchar=fa[i];
      if(fa.size()==1)
	{
	  rt=fa[0];
	  break;
	}
      else if(!no_exponents and i==size)
	{
	  no_exponents=true;
	  i=0;
	  continue;
	}
      else if(!no_division and i==size)
	{
	  no_division=true;
	  i=0;
	  continue;
	}
      else if(!no_multiplication and i==size)
	{
	  no_multiplication=true;
	  i=0;
	  continue;
	}
      else if(!no_addition and i==size)
	{
	  no_addition=true;
	  i=0;
	  continue;
	}
      else if(!no_subtraction and i==size)
	{
	  no_subtraction=true;
	  i=0;
	  continue;
	}
      else if(fchar==power)
	{
	  calc_result=get_math_operator(fa[i-1], fa[i+1], fa[i]);
	  fa=replace_in_vector(fa, to_string(calc_result), i-1, i+1);
	  size=fa.size()-1;
	  i=0;
	  continue;
	}
      else if(fchar==divide and no_exponents)
	{
	  calc_result=get_math_operator(fa[i-1], fa[i+1], fa[i]);
	  fa=replace_in_vector(fa, to_string(calc_result), i-1, i+1);
	  size=fa.size()-1;
	  i=0;
	  continue;
	}
      else if(fchar==multiply and no_exponents)
	{
	  calc_result=get_math_operator(fa[i-1], fa[i+1], fa[i]);
	  fa=replace_in_vector(fa, to_string(calc_result), i-1, i+1);
	  size=fa.size()-1;
	  i=0;
	  continue;
	}
      else if(fchar==add and no_exponents and no_multiplication and no_division)
	{
	  calc_result=get_math_operator(fa[i-1], fa[i+1], fa[i]);
	  fa=replace_in_vector(fa, to_string(calc_result), i-1, i+1);
	  size=fa.size()-1;
	  i=0;
	  continue;
	}
      else if(fchar==subtract and no_exponents and no_multiplication and no_division)
	{
	  calc_result=get_math_operator(fa[i-1], fa[i+1], fa[i]);
	  fa=replace_in_vector(fa, to_string(calc_result), i-1, i+1);
	  size=fa.size()-1;
	  i=0;
	  continue;
	}
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

  int i=0, fa_size=fa.size(), o_index, c_index;
  string fchar;
  vector<string> rt_value;
  vector<int> parenthesis_open_indices, parenthesis_close_indices;

  while(i<=fa_size-1)
    {
      fchar=fa[i];
      // cout<<"i="<<i<<"/"<<fa_size-1<<", "<<fchar<<endl;
      if(fchar==open_parenthesis)
	{
	  parenthesis_open_indices.push_back(i);
	  // cout<<"open "<<i<<" "<<fchar<<endl;
	}
      else if(fchar==close_parenthesis)
	{
	  parenthesis_close_indices.push_back(i);
	  // cout<<"close "<<i<<" "<<fchar<<endl;

	  if(parenthesis_close_indices.size()==1 and parenthesis_open_indices.size()>=1)
	    {
	      o_index=parenthesis_open_indices.back();
	      c_index=parenthesis_close_indices.back();
	      // cout<<o_index<<" "<<c_index<<" corresp. to "<<fa[o_index]<<" "<<fa[c_index]<<endl;
	      rt_value=get_elem(fa, o_index, c_index);
	      fa=replace_in_vector(fa, calculate_order_of_operations(rt_value, rt_value.size()-1), o_index, c_index);
	      parenthesis_open_indices.clear();
	      parenthesis_close_indices.clear();
	      fa_size=fa.size();
	      i=0;
	      continue;
	    }
	}
      i++;
    }
  // cout<<"final result (end) "<<calculate_order_of_operations(fa, fa.size()-1)<<endl;
  return calculate_order_of_operations(fa, fa.size()-1);
}

string equation_read(string func_name, string func_value)
{
  int i=0, last_operator_index;
  vector<string> fa;
  string abb="", fchar;

  while(i<=func_value.size()-1)
    {
      fchar=func_value[i];
      // cout<<"fchar "<<fchar<<endl;
      if(is_operator(fchar) and i==0)
	{
	  fa.push_back(fchar);
	}
      else if(is_operator(fchar))
	{
	  if(abb.length()>0)
	    {
	      fa.push_back(abb);
	      abb="";
	    }
	  fa.push_back(fchar);
	  last_operator_index=i;
	}
      else
	{
	  abb=abb+func_value[i];
	}
      i++;
    }

  if(last_operator_index!=func_value.size()-1)
    {
      fa.push_back(func_value.substr(last_operator_index+1, func_value.size()-1-last_operator_index));
    }
  // cout<<"calc eq constants"<<endl;
  return calculate_equation_constants(fa);
}

tuple<string, string> read_equations(string line)
{

  int i=0;
  string fchar, ab, empty_str="", equation_name, equation_value;
  vector<string> empty;
  vector<double> values;
  bool eq_found=false;

  while(i<=line.size()-1)
  {
    fchar=line[i];
      if(fchar==";")
	{
	  equation_value=ab;
	}
      else if(fchar=="\0" or fchar==" " or fchar.empty())
	{
	  i++;
	  continue;
	}
      else if(fchar=="=")
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

  // cout<<"read eq "<<equation_name<<" "<<equation_value<<endl;
  return make_tuple(equation_name, equation_read(equation_name, equation_value));
}

string get_variable(string line)
{

  int i=0;
  string fchar, variable, ab;

  while(i<=line.size()-1)
    {
      fchar=line[i];

      if(fchar==";")
	{
	  variable=ab;
	  break;
	}
      else if(fchar=="\0" or fchar==" " or fchar.empty())
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

  fstream bin_loaded("bin", ios_base::in | ios::binary);
  string line;
  bool constants_found=false, equations_found=false, variables_found=false, constants_saved=false, equations_saved=false, variables_saved=false;
  vector<tuple<string, string>> rt;

  while(getline(bin_loaded, line))
    {
      if(line.empty())
	{
	  continue;
	}
      else if(line_commented_or_not(line).empty())
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
	      cout<<get_variable(line)<<endl;
	      variables.push_back(get_variable(line));
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
	      func_params.push_back(read_constants(line));
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
	      rt.push_back(read_equations(line));
	    }
	}
    }

  // cout<<"########equation_read end########"<<endl;
  return rt;
}

int main()
{

  int i=0;
  vector<tuple<string, string>> result=read_bin();
  cout<<"Equation values are: "<<endl;

  while(i<=result.size()-1)
    {
      cout<<get<0>(result[i])<<" "<<get<1>(result[i])<<endl;
      i++;
    }
  // cout<<result<<endl;
  return 0;
}

double get_constant_value(string constant)
{

  int i=0;
  bool value_found=false;
  double value_found_return;

  while(i<=func_params.size()-1)
    {
      if(constant==get<0>(func_params[i]))
	{
	  value_found=true;
	  value_found_return=get<1>(func_params[i]);
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
      cout<<constant<<" not found"<<endl;
      return NAN;
    }
}
