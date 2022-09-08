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
