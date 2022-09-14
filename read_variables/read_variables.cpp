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

vector<string> print_elem(vector<string> fa, int start, int stop)
{
  int i=start;
  string emp="";
  vector<string> rt;
  while(i<=stop)
    {
      rt.push_back(fa[i]);
      i++;
    }
  return rt;
}

string calc123(vector<string> fa, int size)
{
  int i=0, open_parenthesis_index, close_parenthesis_index;
  bool no_exponents=false, no_division=false, no_multiplication=false, no_addition=false, no_subtraction=false;
  string fchar, rt;
  double calc_result;

  while(i<=size)
    {
      fchar=fa[i];
      // cout<<i<<"/"<<size<<" "<<fchar<<endl;
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


void calculate_equation_constants(vector<string> fa)
{

  /*
    Calculates an equation according to order of operations:

    1. Parentheses
    2. Exponents
    3. Multiplication and division
    4. Addition and subtraction
  */

  int i=0, j=0;
  bool no_exponents=false, no_division=false, no_multiplication=false, no_addition=false, no_subtraction=false, no_open_parenthesis=false, no_close_parenthesis=false,  open_parenthesis_found=false, close_parenthesis_found=false;
  string fchar;
  double calc_result;
  vector<string> rt_value;
  vector<int> parenthesis_open_indices, parenthesis_close_indices;

  while(i<=fa.size()-1)
    {
      fchar=fa[i];
      // cout<<"non paran "<<fchar<<endl;
      if(fchar==open_parenthesis)
	{
	  parenthesis_open_indices.push_back(i);
	  cout<<"open parenthesis found at index "<<i<<endl;
	}
      else if(fchar==close_parenthesis)
	{
	  parenthesis_close_indices.push_back(i);
	  cout<<"close parenthesis found at index "<<i<<endl;
	}
      i++;
    }
  cout<<"sizes "<<parenthesis_open_indices.size()<<" "<<parenthesis_close_indices.size()<<endl;

  // int c=0;
  // int c2=parenthesis_open_indices.size();
  // while(c<=parenthesis_open_indices.size()-1)
  //   {
  //     // cout<<c2-c<<" "<<c<<endl;
  //     cout<<parenthesis_open_indices[c2-c]<<" "<<parenthesis_close_indices[c]<<endl;
  //     c++;
  //   }

  if(parenthesis_open_indices.size()==1 and parenthesis_close_indices.size()==1)
    {
      rt_value=print_elem(fa, parenthesis_open_indices[0]+1, parenthesis_close_indices[0]-1);
      fa=replace_in_vector(fa, calc123(rt_value, rt_value.size()-1), parenthesis_open_indices[0], parenthesis_close_indices[0]);
    }

  calc123(fa, fa.size()-1);

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
      else if(is_operator(fchar2))
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
