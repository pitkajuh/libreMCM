/*
  Created: 28.08.2022 13:49

  Author: jp
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
#include "read_variables.h"
// #include "global.h"
using namespace std;

const string multiply="*";
const string divide="/";
const string add="+";
const string subtract="-";
const string power="^";
const string open_parenthesis="(";
const string close_parenthesis=")";
const string comment="//";

void calculation_done_function(vector<string> fa, int operator_indice)
{
  double calc_result;
  calc_result=get_math_operator(fa[operator_indice-1], fa[operator_indice+1], fa[operator_indice]);
  cout<<calc_result<<endl;
  replace_in_vector(fa, calc_result, operator_indice);
}


void replace_in_vector(vector<string> fa, double result, int operator_indice)
{
  int i=0;
  int j=0;
  vector<string> fa_edited;
  cout<<"sdasd "<<fa.size()<<" "<<fa[0]<<" "<<fa[fa.size()-1]<<endl;
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
      cout<<fa_edited[j]<<endl;
      j++;
    }
  // replace elements corresponding to indices operator_indice, operator_indice+1 and operator_indice-1 with to_string(result)
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




bool is_string_numerical_value(string variable)
{
  // Checks whether there are numbers(0-9) in the equations, not only variables. Returns true, if string is a valid number.
  return regex_match(variable, regex("^(-?)(0|([1-9][0-9]*))(\\.[0-9]+)?$"));
}

double is_number_or_variable(string ab)
{
  // string parameter_value;
  double parameter_value;
  bool is_number;

  is_number=is_string_numerical_value(ab);
  if(is_number)
    {
      parameter_value=stod(ab);
    }
  else
    {
      // parameter_value=to_string(get_variable_value(ab));
      parameter_value=get_variable_value(ab);
    }
  return parameter_value;
}


double get_math_operator(string value11, string value22, string math_operator)
{

  double value1=is_number_or_variable(value11);
  double value2=is_number_or_variable(value22);

  if(math_operator==multiply)
    {
      cout<<"calculating "<<value1<<"*"<<value2<<"="<<value1*value2<<endl;
      return value1*value2;
    }
  else if(math_operator==add)
    {
      cout<<"calculating "<<value1<<"+"<<value2<<"="<<value1+value2<<endl;
      return value1+value2;
    }
  else if(math_operator==divide)
    {
      cout<<"calculating "<<value1<<"/"<<value2<<"="<<value1/value2<<endl;
      return value1/value2;
    }
  else if(math_operator==subtract)
    {
      cout<<"calculating "<<value1<<"-"<<value2<<"="<<value1-value2<<endl;
      return value1-value2;
    }
  else if(math_operator==power)
    {
      cout<<"calculating "<<value1<<"^"<<value2<<"="<<pow(value1, value2)<<endl;
      return pow(value1, value2);
    }
  else
    {
      return NAN;
    }
}

bool is_operator(string elem)
{
  if(elem==add)
    {
      return true;
    }
  else if(elem==subtract)
    {
      return true;
    }
  else if(elem==multiply)
    {
      return true;
    }
  else if(elem==divide)
    {
      return true;
    }
  else if(elem==power)
    {
      return true;
    }
  else if(elem==open_parenthesis)
    {
      return true;
    }
  else if(elem==close_parenthesis)
    {
      return true;
    }
  else
    {
      return false;
    }
}

bool skip_indice_or_not(int indice, vector<int> indices_to_skip)
{
  int i=0;
  bool skip_or_not=false;
  while(i<=indices_to_skip.size()-1)
    {
      if(indice==indices_to_skip [i])
	{
	  skip_or_not=true;
	  break;
	}
      i++;
    }
  return skip_or_not;
}
