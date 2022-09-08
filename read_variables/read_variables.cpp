/*
  Created: 22.04.2022 18:35

  Author: pitkajuh
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
#include "helpers.h"

using namespace std;

// global variables
const string multiply="*";
const string divide="/";
const string add="+";
const string subtract="-";
const string power="^";
const string open_parenthesis="(";
const string close_parenthesis=")";
const string comment="//";
vector<tuple<string, double>> func_params;

tuple<string, double> read_variables(string line)
{
  int i; // index
  string ab, empty_str=""; // empty strings used for appending
  const int line_ln=line.length();
  bool eq_found=false;
  string value;
  tuple<string, double> values1;
  double variable_value;
  string variable_name;

  if(line.find(comment)==string::npos) // skips the line if it is commented out
    {
      while(i<=line_ln)
	{
	  if(line[i]==';')
	    {
	      variable_value=stod(ab);
	    }
	  if(line[i]=='=')
	    {
	      variable_name=ab;
	      ab=empty_str;
	      eq_found=true;
	      i++;
	    }
	  if(isblank(line[i]) or line[i]=='\0')
	    {
	      i++;
	      continue;
	    }
	  else
	    {
	      ab=ab+line[i];
	    }
	  i++;
	}
      values1=make_tuple(variable_name, variable_value);
      return values1;
    }
}


double get_variable_value(string variable)
{
  int i=0;
  bool value_found=false;
  double value_found_return;
  while(i<=func_params.size()-1)
    {
      if(variable==get<0>(func_params[i]))
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
      return NAN;
    }
}

vector<string> get_values_from_vector(vector<string> get_values_from, int indice_from, int indice_to)
{
  int i=indice_from+1;
  vector<string> return_values;
  while(i<=indice_to-1)
    {
      return_values.push_back(get_values_from[i]);
      i++;
    }
  return return_values;
}

void replace_in_vector(vector<string> fa, double result, int operator_indice)
{
  int i=0;
  int j=0;
  vector<string> fa_edited;

  while(i<=fa.size()-1)
    {
      if(fa.size()==3 and fa[0]==open_parenthesis and fa[fa.size()-1]==close_parenthesis)
	{
	  fa_edited.push_back(to_string(result));
	  break;
	}
      else if(i==operator_indice-1)
	{
	  i++;
	  continue;
	}
      else if(i==operator_indice)
	{
	  fa_edited.push_back(to_string(result));
	}
      else if(i==operator_indice+1)
	{
	  i++;
	  continue;
	}
      else
	{
	  fa_edited.push_back(fa[i]);
	}
      i++;
    }

  while(j<=fa_edited.size()-1)
    {

      j++;
    }
}

void calculation_done_function(vector<string> fa, int operator_indice)
{
  double calc_result;
  calc_result=get_math_operator(fa[operator_indice-1], fa[operator_indice+1], fa[operator_indice]);

  replace_in_vector(fa, calc_result, operator_indice);
}

tuple<string, int, int> calculate(vector<string> fa, int size_original_equation)
{
  /*
    Calculates an equation according to order of operations:

    1. Exponents
    2. Multiplication and division
    3. Addition and subtraction
  */

  int i=0, operator_index, number1_index, number2_index;
  bool no_exponents=false, no_division=false, no_multiplication=false, no_addition=false, no_subtraction=false;
  string fchar;
  double calc_result;
  vector<int> calculation_done_indices;
  tuple<string, int, int> rt_value;

  int element_indices_to_delete=size_original_equation-2;



  while(i<=fa.size()-1)
    {
      fchar=fa[i];

      if(!no_exponents and i==fa.size()-1)
	{
	  i=0;
	  no_exponents=true;
	}
      else if(!no_division and i==fa.size()-1)
	{
	  i=0;
	  no_division=true;
	}
      else if(!no_multiplication and i==fa.size()-1)
	{
	  i=0;
	  no_multiplication=true;
	}
      else if(!no_addition and i==fa.size()-1)
	{
	  i=0;
	  no_addition=true;
	}
      else if(!no_subtraction and i==fa.size()-1)
	{
	  i=0;
	  no_subtraction=true;
	}
      else if(fchar==power)
	{
	  cout<<"power"<<endl;
	}
      else if(fchar==divide and !no_exponents)
	{
	  cout<<"divide"<<endl;
	}
      else if(fchar==multiply and !no_exponents)
	{
	  cout<<"multiply"<<endl;
	}
      else if(fchar==add and !no_addition and !no_subtraction)
	{
	  operator_index=i;
	  number1_index=i-1;
	  number2_index=i+1;
	  calc_result=get_math_operator(fa[number1_index], fa[number2_index], fa[operator_index]);
	  break;
	}
      else if(fchar==subtract and !no_addition and !no_subtraction)
	{
	  cout<<"minus"<<endl;
	}
      i++;
    }

  return make_tuple(to_string(calc_result), number1_index, number2_index);
}

void calculate_equation_constants(vector<string> fa)
{
  int i=0, j=0, parenthesis_open_nr=0, parenthesis_close_nr=0;
  vector<int> open_parenthesis_indices;
  vector<int> close_parenthesis_indices;
  bool parenthesis_open_found=false, parenthesis_close_found=false;
  vector<string> values_for_calculating;
  string fchar;
  tuple<string, int, int> calculation_result;
  int open_parenthesis_indice, close_parenthesis_indice, number1_index, number2_index;
  vector<int> numbers_to_calculate_indices;



  while(i<=fa.size()-1)
    {
      fchar=fa[i];

      if(fchar==open_parenthesis)
	{
	  open_parenthesis_indices.push_back(i);
	  parenthesis_open_found=true;
	  parenthesis_open_nr++;
	}
      else if(fchar==close_parenthesis)
	{
	  close_parenthesis_indices.push_back(i);
	  parenthesis_close_found=true;
	  parenthesis_close_nr++;
	}
      else if(!is_operator(fchar))
	{
	  numbers_to_calculate_indices.push_back(i);

	}
      else if(parenthesis_open_found and parenthesis_close_found)
	{
	  if(open_parenthesis_indices.size()==1 and close_parenthesis_indices.size()==1)
	    {
	      open_parenthesis_indice=open_parenthesis_indices[0];
	      close_parenthesis_indice=close_parenthesis_indices[0];
	      calculation_result=calculate(get_values_from_vector(fa, open_parenthesis_indice, close_parenthesis_indice), fa.size());
	      // replace_in_vector(fa, stod(get<0>(calculation_result)), get<2>(calculation_result));
	      numbers_to_calculate_indices.clear();
	    }
	  parenthesis_close_found=false;
	  parenthesis_open_found=false;
	}
      // else if(parenthesis_open_found and parenthesis_close_found and parenthesis_open_nr>>parenthesis_close_found)
      // {
      //   //laske
      // }
      i++;
    }
}


void equation_read(string func_name, string func_value)
{
  int i=0;
  vector<string> fa;
  string abb="";
  string fchar, fchar2;
  int last_operator_index;

  while(i<=func_value.size()-1)
    {
      fchar2=func_value[i];

      if(is_operator(fchar2) and i==0)
	{
	  fa.push_back(fchar2);

	}
      else if(is_operator(fchar2) )
	{

	  if(abb.length()>0)
	    {
	      fa.push_back(abb);

	      abb="";
	    }
	  fa.push_back(fchar2);
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



  int j=0;

  string tyhja="";
  while(j<=fa.size()-1)
    {
      tyhja=tyhja+fa[j];

      j++;
    }
  if(tyhja==func_value)
    {
      cout<<func_value<<" ok"<<endl;
    }
  else
    {
      cout<<func_value<<" not ok"<<endl;
    }
  calculate_equation_constants(fa);
}

void read_equations(string line)
{
  // reads the equation from a file
  int i=0; // index
  string ab, empty_str=""; // empty strings used for appending
  const int line_ln=line.length();
  vector<string> empty;
  vector<double> values;
  bool eq_found=false;
  string value;
  string value1;
  if(line.find(comment)==string::npos)
    { // skips the line if it is commented out
      while(i<=line_ln-1)
	{


	  if(line[i]==';')
	    {

	      // values.push_back(stod(ab));

	      value1=ab;
	    }
	  else if(isblank(line[i]) or line[i]=='\0')
	    {

	      i++;
	      continue;
	    }
	  else if(line[i]=='=')
	    {

	      // empty.push_back(ab);

	      value=ab;
	      ab=empty_str;
	      eq_found=true;
	      // i++;
	    }
	  else
	    {

	      ab=ab+line[i];
	    }
	  i++;
	}

      equation_read(value, value1);
    }
}

int main()
{
  fstream variables_loaded("bin", ios_base::in | ios::binary);
  string line;
  bool variables_found=false;
  bool equations_found=false;
  bool compartments_found=false;
  bool variables_saved=false;
  bool equations_saved=false;
  bool compartments_saved=false;

  while(getline(variables_loaded, line))
    {

      if(line.empty())
	{
	  continue;
	}
      if(not variables_saved)
	{
	  if(line=="}" and variables_found)
	    {
	      variables_saved=true;
	      continue;
	    }
	  if(line=="variables" or line=="variables{")
	    {
	      variables_found=true;
	      continue;
	    }
	  if(variables_found)
	    {
	      func_params.push_back(read_variables(line));
	    }
	}
      if(not equations_saved)
	{
	  if(line=="}" and equations_found)
	    {
	      variables_saved=true;
	      continue;
	    }
	  if(line=="equations" or line=="equations{")
	    {
	      equations_found=true;
	      continue;
	    }
	  if(equations_found)
	    {
	      read_equations(line);
	    }
	}
    }


  return 0;
}
