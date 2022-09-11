/*
  Created: 22.04.2022 18:35

  Author: pitkajuh
*/

/*
Gets from the variables section from bin file and calculates the equations as described in the equations section of the bin file.
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



tuple<string, int, int> calculate(vector<string> fa, int size_original_equation, int open_parenthesis_indice, int close_parenthesis_indice)
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
  int fa_size=fa.size();

// if(fa_size==3)
//   {
//     replace whole fa
//   }

  cout<<"size in calculation "<<fa.size()<<" size original "<<size_original_equation<<" indices "<<open_parenthesis_indice<<" "<<close_parenthesis_indice<<endl;
  // cout<<"######calculate#######"<<endl;

  while(i<=fa.size()-1)
    {
      fchar=fa[i];
      // cout<<fchar<<" "<<i<<endl;

      if(!no_exponents and i==fa.size()-1)
	{
	  i=0;
	  no_exponents=true;
	  // cout<<"no_exponents"<<endl;
	  continue;
	}
      else if(!no_division and i==fa.size()-1)
	{
	  i=0;
	  no_division=true;
	  // cout<<"no_division"<<endl;
	  continue;
	}
      else if(!no_multiplication and i==fa.size()-1)
	{
	  i=0;
	  no_multiplication=true;
	  // cout<<"no_multi"<<endl;
	  continue;
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
	  operator_index=i;
	  number1_index=i-1;
	  number2_index=i+1;
	  calc_result=get_math_operator(fa[number1_index], fa[number2_index], fa[operator_index]);
	  break;
	}
      else if(fchar==divide and no_exponents)
	{
	  operator_index=i;
	  number1_index=i-1;
	  number2_index=i+1;
	  calc_result=get_math_operator(fa[number1_index], fa[number2_index], fa[operator_index]);
	  break;
	}
      else if(fchar==multiply and no_exponents)
	{
	  operator_index=i;
	  number1_index=i-1;
	  number2_index=i+1;
	  calc_result=get_math_operator(fa[number1_index], fa[number2_index], fa[operator_index]);
	  break;
	}
      else if(fchar==add and no_exponents and no_multiplication and no_division)
	{
	  // Replace the elements which have been calculated with the result of the calculation and return the vector, repeat the process until all calculations have been done.
	  operator_index=i;
	  number1_index=i-1;
	  number2_index=i+1;
	  calc_result=get_math_operator(fa[number1_index], fa[number2_index], fa[operator_index]);
	  break;
	}
      else if(fchar==subtract and no_exponents and no_multiplication and no_division)
	{
	  operator_index=i;
	  number1_index=i-1;
	  number2_index=i+1;
	  calc_result=get_math_operator(fa[number1_index], fa[number2_index], fa[operator_index]);
	  break;
	}
      i++;
    }
  // cout<<"result "<<calc_result<<" 1st index "<<number1_index<<" 2nd index "<<number2_index<<" fa size "<<fa.size()<<endl;
  return make_tuple(to_string(calc_result), number1_index, number2_index);
}

void calculate_equation_constants(vector<string> fa)
{
  int i=0, j=0, parenthesis_open_nr=0, parenthesis_close_nr=0, open_parenthesis_indice, close_parenthesis_indice, number1_index, number2_index;
  vector<int> open_parenthesis_indices, close_parenthesis_indices;
  bool parenthesis_open_found=false, parenthesis_close_found=false;
  vector<string> values_for_calculating;
  string fchar;
  tuple<string, int, int> calculation_result;

  vector<int> numbers_to_calculate_indices;

  cout<<"######## calculate constants#######"<<endl;

  while(i<=fa.size()-1)
    {
      fchar=fa[i];
      // cout<<i<<" "<<fchar<<endl;
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
	  // cout<<numbers_to_calculate_indices.size()<<" nr index "<<i<<endl;
	}
      else if(parenthesis_open_found and parenthesis_close_found)
	{
	  if(open_parenthesis_indices.size()==1 and close_parenthesis_indices.size()==1)
	    {
	      open_parenthesis_indice=open_parenthesis_indices[0];
	      close_parenthesis_indice=close_parenthesis_indices[0];
	      // cout<<"result idasds "<<calculate(get_values_from_vector(fa, open_parenthesis_indice, close_parenthesis_indice))<<endl;

	      // cout<<"open_parenthesis_indice "<<open_parenthesis_indice<<" close_parenthesis_indice "<<close_parenthesis_indice<<endl;

	      calculation_result=calculate(get_values_from_vector(fa, open_parenthesis_indice, close_parenthesis_indice), fa.size(), open_parenthesis_indice, close_parenthesis_indice);

	      // cout<<"to replace from index "<<open_parenthesis_indice+1+get<1>(calculation_result)<<" to index "<<open_parenthesis_indice+1+get<2>(calculation_result)<<endl;



	      // cout<<"result idasds "<<calculate(get_values_from_vector(fa, open_parenthesis_indice, close_parenthesis_indice))<<endl;

	      // cout<<"calculation result "<<get<0>(calculation_result)<<" "<<get<1>(calculation_result)<<" "<<get<2>(calculation_result)<<" size "<<fa.size()<<endl;
	      fa=replace_in_vector(fa, get<0>(calculation_result), open_parenthesis_indice+1+get<1>(calculation_result), open_parenthesis_indice+1+get<2>(calculation_result));
	      numbers_to_calculate_indices.clear();
	      i=0;
	      continue;
	    }
	  parenthesis_close_found=false;
	  parenthesis_open_found=false;
	}
      // else if(parenthesis_open_found and parenthesis_close_found and parenthesis_open_nr>>parenthesis_close_found)
      // {
      //   //calculate
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
      // cout<<fchar2<<endl;
      if(is_operator(fchar2) and i==0)
	{
	  fa.push_back(fchar2);
	  // cout<<<<endl;<<"appendign1 :"<<fchar2<<":"<<endl;
	}
      else if(is_operator(fchar2))
	{
	  if(abb.length()>0)
	    {
	      fa.push_back(abb);
	      // cout<<"appendign :"<<abb<<":"<<" "<<abb.length()<<endl;
	      abb="";
	    }
	  fa.push_back(fchar2);
	  last_operator_index=i;
	  // cout<<"appendign :"<<fchar2<<":"<<endl;
	}
      else
	{
	  abb=abb+func_value[i];
	}
      i++;
    }

  if(last_operator_index!=func_value.size()-1)
    {
      // cout<<last_operator_index+1<< func_value.size()-1-last_operator_index<<endl;
      // cout<<func_value.substr(last_operator_index+1, func_value.size()-1-last_operator_index)<<endl;

      fa.push_back(func_value.substr(last_operator_index+1, func_value.size()-1-last_operator_index));
    }

  // cout<<last_operator_index<<" "<<func_value.size()-1<<" "<<func_value[last_operator_index]<<endl;

  // int j=0;
  // cout<<"#####printign vector#####"<<endl;
  // string tyhja="";
  // while(j<=fa.size()-1)
  //   {
  //     tyhja=tyhja+fa[j];
  //     // cout<<fa[j]<<endl;
  //     j++;
  //   }
  // if(tyhja==func_value)
  //   {
  //     cout<<func_value<<" ok"<<endl;
  //   }
  // else
  //   {
  //     cout<<func_value<<" ei ok"<<endl;
  //   }

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
	  // cout<<line<<" "<<line_ln<<endl;
	  // cout<<i<<" "<<line[i]<<endl;
	  if(line[i]==';')
	    {
	      // cout<<"if 1 "<<i<<endl;
	      // values.push_back(stod(ab));
	      // cout<<"funcs "<<ab<<endl;
	      value1=ab;
	    }
	  else if(isblank(line[i]) or line[i]=='\0')
	    {
	      // cout<<"if 3 "<<i<<endl;
	      i++;
	      continue;
	    }
	  else if(line[i]=='=')
	    {
	      // cout<<"if 2 "<<i<<endl;
	      // empty.push_back(ab);
	      // cout<<"funcs "<<ab<<endl;
	      value=ab;
	      ab=empty_str;
	      eq_found=true;
	      // i++;
	    }
	  else
	    {
	      // cout<<<<endl;<<"else "<<i<<endl;
	      ab=ab+line[i];
	    }
	  i++;
	}
      cout<<"read eq "<<value<<" "<<value1<<endl;
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
      // cout<<line.empty()<<endl;
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
  cout<<"########equation_read end########"<<endl;

  return 0;
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
