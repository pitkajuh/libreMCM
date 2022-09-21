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
#include "read_bin.h"
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


vector<string> replace_in_vector(vector<string> fa, string result, int index_replace_from, int index_replace_to)
{

  int i=0, j=0, k=0;
  vector<string> fa_edited;
  string fchar, empty, empty2;

  // cout<<"replace between indices "<<index_replace_from<<" and "<<index_replace_to<<endl;

  // while(k<=fa.size()-1)
  //   {
  //     empty2=empty2+fa[k];
  //     k++;
  //   }

  if(index_replace_to-index_replace_from==2 and fa[index_replace_from-1]==open_parenthesis and fa[index_replace_to+1]==close_parenthesis)
    {
      // cout<<"abc123"<<endl;
      index_replace_from=index_replace_from-1;
      index_replace_to=index_replace_to+1;
    }
  while(i<=fa.size()-1)
    {
      fchar=fa[i];
      // cout<<"replace in vector "<<i<<"/"<<fa.size ()-1<<" "<<fa[i]<<endl;
      if(i==index_replace_from)
	{
	  fa_edited.push_back(result);
	}
      else if(i==index_replace_to)
	{
	  i++;
	  continue;
	}
      else if(i>index_replace_from and i<index_replace_to)
	{
	  i++;
	  continue;
	}
      else
	{
	  fa_edited.push_back(fchar);
	}
      i++;
    }

  // while(j<=fa_edited.size()-1)
  //   {
  //     empty=empty+fa_edited[j];
  //     // cout<<"edited "<<j<<"/"<<fa_edited.size()-1<<" "<<fa_edited[j]<<endl;
  //     j++;
  //   }
  // cout<<"returning edited vector "<<empty<<" size:"<<fa_edited.size()<<" original "<<empty2<<endl;
  return fa_edited;
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

// tuple<string, double> read_variables(string line)
// {

//   int i;
//   string fchar, ab, empty_str="", variable_name, value;
//   bool eq_found=false;
//   tuple<string, double> values1;
//   double variable_value;

//   while(i<=line.size ()-1)
//     {
//       fchar=line[i];
//       if(fchar==";")
// 	{
// 	  // variable_value=ab;
// 	  variable_value=stod(ab);
// 	}
//       else if(fchar=="=")
// 	{
// 	  variable_name=ab;
// 	  ab=empty_str;
// 	  eq_found=true;
// 	  i++;
// 	}
//       else if(fchar=="\0" or fchar==" " or fchar.empty())
// 	{
// 	  i++;
// 	  continue;
// 	}
//       else
// 	{
// 	  ab=ab+fchar;
// 	}
//       i++;
//     }
//   values1=make_tuple(variable_name, variable_value);
//   return values1;
// }

tuple<string, double> read_constants(string line)
{

  int i;
  string fchar, ab, empty_str="", constant_name, value; // empty strings used for appending
  bool eq_found=false;
  tuple<string, double> values1;
  double constant_value;

  while(i<=line.size ()-1)
    {
      if(line[i]==';')
	{
	  // cout<<"to double "<<ab<<" "<<typeid(ab).name()<<endl;0
	  constant_value=stod(ab);
	}
     if(line[i]=='=')
	{
	  constant_name=ab;
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
  values1=make_tuple(constant_name, constant_value);
  return values1;
}

bool is_string_numerical_value(string constant)
{
  // Checks whether there are numbers(0-9) in the equations, not only constants. Returns true, if string is a valid number.
  return regex_match(constant, regex("^(-?)(0|([1-9][0-9]*))(\\.[0-9]+)?$"));
}

double is_number_or_constant(string ab)
{

  double parameter_value;
  bool is_number;

  is_number=is_string_numerical_value(ab);
  if(is_number)
    {
      parameter_value=stod(ab);
    }
  else
    {
      parameter_value=get_constant_value(ab);
    }
  return parameter_value;
}


double get_math_operator(string value1_input, string value2_input, string math_operator)
{

  double value1=is_number_or_constant(value1_input), value2=is_number_or_constant(value2_input);

  if(math_operator==multiply)
    {
      // cout<<"calculating "<<value1<<"*"<<value2<<"="<<value1*value2<<endl;
      return value1*value2;
    }
  else if(math_operator==add)
    {
      // cout<<"calculating "<<value1<<"+"<<value2<<"="<<value1+value2<<endl;
      return value1+value2;
    }
  else if(math_operator==divide)
    {
      // cout<<"calculating "<<value1<<"/"<<value2<<"="<<value1/value2<<endl;
      return value1/value2;
    }
  else if(math_operator==subtract)
    {
      // cout<<"calculating "<<value1<<"-"<<value2<<"="<<value1-value2<<endl;
      return value1-value2;
    }
  else if(math_operator==power)
    {
      // cout<<"calculating "<<value1<<"^"<<value2<<"="<<pow(value1, value2)<<endl;
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
      if(indice==indices_to_skip[i])
	{
	  skip_or_not=true;
	  break;
	}
      i++;
    }
  return skip_or_not;
}

string line_commented_or_not(string line)
{

  int i=0, index_from, index_to;
  string fchar, fchar_p1, line_return="", empty="", empty2=" ";

  while (i<=line.size()-1)
    {
      fchar=line[i];
      fchar_p1=line[i+1];
      // if(line[i]=='/' and line[i+1]=='/')
      if(fchar=="/" and fchar_p1=="/")
	{
	  break;
	}
      // else if(fchar==" " or isblank(fchar) or fchar=="\0")
      else if(fchar==" " or fchar=="\0" or fchar.empty())
	{
	  // cout<<"tyhja 123123"<<endl;
	  i++;
	  continue;
	}
      else
	{
	  line_return=line_return+line[i];
	}
      i++;
    }
  // cout<<"########"<<endl;
  // cout<<"rt line "<<line<<endl;
  // cout<<"########"<<endl;
  return line_return;
}
