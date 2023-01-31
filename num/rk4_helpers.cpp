/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <tuple>
#include <string>
#include <vector>
#include "rk4.h"
#include "../global/global.h"
#include "../wdata/values_to_graph.h"
#include "../math/calculate_order_of_operations.h"
#include "../rcompartment/read_compartment_definition.h"
#include "../util/vector_convert.h"
#include "../util/string_split.h"
#include "../util/replace_in_vector.h"

using namespace std;

int asd=0;

string get_last_value(string param)
{
  int i=0;
  int j=0;
  int k=0;
  string parameter_name;
  string parameter_value;
  string comp_name;
  vector<string> parameters_empty;
  string parameters_empty_j;
  vector<tuple<string, vector<string>>> empty_vec;
  tuple<string, vector<string>> empty_vec_j;
  bool found=false;
  tuple<string, string> fg=split_string_in_two(param, parm_delim);
  tuple<string, string> agh;
  string compartment_name_wanted=get<0>(fg);
  string parameter_name_wanted=get<1>(fg);


  tuple<
	     string, // compartment name
	     vector<
	            tuple<
	                  string, // parameter name
	                  vector<
	                  string // parameter values
	                 >
      >     >      >
       params_graph_i;

  while(i<=params_graph.size()-1)
    {
      if(found)
	{
	  break;
	}

      params_graph_i=params_graph[i];
      comp_name=get<0>(params_graph_i);
      empty_vec=get<1>(params_graph_i);

      while(j<=empty_vec.size()-1)
	{
	  if(found)
	    {
	      break;
	    }

	  parameter_name=get<0>(empty_vec[j]);
	  parameters_empty=get<1>(empty_vec[j]);

	  agh=split_string_in_two(parameter_name, parm_delim);
	  comp_name=get<0>(agh);
	  parameter_name=get<1>(agh);

	  if(compartment_name_wanted==comp_name)
	    {
	      while(k<=parameters_empty.size()-1)
		{
		  if(parameter_name==parameter_name_wanted)
		    {
		      parameter_value=parameters_empty[parameters_empty.size()-1];
		      found=true;
		      break;
		    }
		  k++;
		}
	    }
	  k=0;
	  j++;
	}
      j=0;
      i++;
    }

  return parameter_value;
}

vector<string> get_multiple_last_values(vector<string> vec)
{
  int i=0;
  vector<string> rt;
  string str;
  string str1;

  while(i<=vec.size()-1)
    {
      str=vec[i];
      str1=get_last_value(str);
      rt.push_back(str1);
      i++;
    }

  return rt;
}

vector<string> replace_in_equation(vector<string> equation, int indice, string k_add)
{
  int i=indice;
  string replace;
  string k_add_1st;
  int equation_size=equation.size();
  string fchar;
  vector<string> equation_vec;
  vector<string> replace_vec;

  k_add_1st=k_add[0];
  fchar=equation[i];

  if(k_add_1st==subtract)
    {
      replace=fchar+k_add;
    }
  else
    {
      replace=fchar+add+k_add;
    }

  equation_vec=equation_string_to_equation_vector(replace);
  replace_vec=calculate_order_of_operations2(equation_vec);
  replace=vector_to_string(replace_vec);
  equation=replace_in_vector(equation, replace, i, i);
  equation_size=equation.size();
  return equation;
}

string get_value_for_replace_whole_equation(string compartment_name_split, vector<string> params)
{
  int i=0;
  string global_compartment_names_i;
  int indice;
  string result;

  while(i<=global_compartment_names.size()-1)
    {
      global_compartment_names_i=global_compartment_names[i];

      if(compartment_name_split==global_compartment_names_i)
	{
	  indice=i;
	  break;
	}
      i++;
    }

  result=params[i];
  return result;
}

vector<string> replace_in_whole_equation(vector<string> equation, vector<int> indices, vector<string> params, string addition, vector<vector<string>> param_data)
{
  int i=0;
  tuple<string, string> param_splitted;
  tuple<string, string> string_splitted;
  string compartment_name_split;
  string value;
  string repl;
  vector<string> eq_params=param_data[asd];
  string eq_params_i;
  int indice;

  while(i<=indices.size()-1)
    {
      eq_params_i=eq_params[i];
      indice=indices[i];
      string_splitted=split_string_in_two(eq_params_i, parm_delim);
      compartment_name_split=get<0>(string_splitted);
      repl=get_value_for_replace_whole_equation(compartment_name_split, params);
      equation=replace_in_equation(equation, indice, repl);
      i++;
    }

  asd++;

  return equation;
}

vector<string> values_to_add_update(vector<string> values_to_add, string constant)
{
  int i=0;
  double result;
  string result_str;
  const string zero="0";
  double constant_double;
  string values_to_add_i;
  double values_to_add_i_double;

  if(constant!=zero)
    {
      while(i<=values_to_add.size()-1)
	{
	  values_to_add_i=values_to_add[i];
	  values_to_add_i_double=stod(values_to_add_i);
	  constant_double=stod(constant);
	  result=constant_double*values_to_add_i_double;
	  result_str=to_string(result);
	  values_to_add[i]=result_str;
	  i++;
	}
    }

  return values_to_add;
}

tuple<bool, int> is_in_vector(vector<string> vec, string str_find)
{
  // Checks if a string is in a string of vectors and return true/false and indice.
  int i=0;
  int is_in_indice=-1;
  bool rt=false;
  string fchar;
  tuple<bool, int> result;

  while(i<=vec.size()-1)
    {
      fchar=vec[i];

      if(str_find==fchar)
	{
	  rt=true;
	  is_in_indice=i;
	  break;
	}
      i++;
    }

  result=make_tuple(rt, is_in_indice);
  return result;
}
