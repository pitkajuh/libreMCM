/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "rk4.h"
#include "../global/global.h"
#include "../wdata/values_to_graph.h"
#include "../math/get_math_operator_v2.h"
#include "../rcompartment/read_compartment_definition.h"
#include "../map/create_maps.h"
#include "../util/vector_convert.h"
#include "../util/string_split.h"

using std::to_string;

int param_data_i=0;

string get_last_value(string param)
{
  SplittedString fg=split_string_in_two(param, parm_delim);
  string compartment_name_wanted=fg.splitted_string_part1;
  string parameter_name_wanted=fg.splitted_string_part2;

  map<string, vector<string>> vec_map=compartment_map[compartment_name_wanted];
  vector<string> vec=vec_map[parameter_name_wanted];

  int size=vec.size();
  string value_wanted=vec[size-1];
  string parameter_value=value_wanted;
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
  string k_add_1st;
  string fchar=equation[i];
  string replace;
  k_add_1st=k_add[0];

  if(k_add_1st==subtract)
    {
      replace=fchar+k_add;
    }
  else
    {
      replace=fchar+add+k_add;
    }

  vector<string> equation_vec=equation_string_to_equation_vector(replace);
  string value1=equation_vec[0];
  string value2=equation_vec[2];
  string math_op=equation_vec[1];
  replace=get_math_operator2(value1, value2, math_op);
  equation[i]=replace;
  return equation;
}

string get_value_for_replace_whole_equation(string compartment_name_split, vector<string> params)
{
  int i=0;
  int size=global_compartment_names.size();
  string global_compartment_names_i;
  int indice;
  string result;

  while(i<=size-1)
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

vector<string> replace_in_whole_equation(vector<string> equation, vector<int> indices, vector<string> params, string addition, VecVecString param_data)
{
  int i=0;
  int size=indices.size();
  int indice;
  SplittedString string_splitted;
  string compartment_name_split;
  string value;
  string repl;
  string eq_params_i;
  vector<string> eq_params=param_data.get(param_data_i);

  while(i<=size-1)
    {
      eq_params_i=eq_params[i];
      indice=indices[i];
      string_splitted=split_string_in_two(eq_params_i, parm_delim);
      compartment_name_split=string_splitted.splitted_string_part1;
      repl=get_value_for_replace_whole_equation(compartment_name_split, params);
      equation=replace_in_equation(equation, indice, repl);
      i++;
    }
  param_data_i++;
  return equation;
}

vector<string> values_to_add_update(vector<string> values_to_add, string constant)
{
  int i=0;
  double result;
  double constant_double;
  double values_to_add_i_double;
  const string zero="0";
  string result_str;
  string values_to_add_i;

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
