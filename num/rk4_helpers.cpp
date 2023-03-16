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
#include "../debug/debug.h"

using std::to_string;

int param_data_i=0;

string get_last_value(const SplittedString param)
{
  string compartment_name_wanted=param.splitted_string_part1;
  string parameter_name_wanted=param.splitted_string_part2;

  map<string, vector<string>> vec_map=compartment_map[compartment_name_wanted];
  vector<string> vec=vec_map[parameter_name_wanted];

  const int size=vec.size();
  string value_wanted=vec[size-1];
  string parameter_value=value_wanted;
  return parameter_value;
}

vector<string> get_multiple_last_values(const vector<SplittedString> vec)
{
  vector<string> rt;
  string str;

  for(const auto &i: vec)
    {
      str=get_last_value(i);
      rt.push_back(str);
    }
  return rt;
}

string get_replace(const string fchar, const string k_add)
{
  string k_add_1st;
  string replace;
  k_add_1st=k_add[0];

  if(k_add_1st==SUBTRACT)
    {
      replace=fchar+k_add;
    }
  else
    {
      replace=fchar+ADD+k_add;
    }
  return replace;
}

vector<string> replace_in_equation(vector<string> equation, const int indice, const string k_add)
{
  string fchar=equation[indice];
  string replace=get_replace(fchar, k_add);
  vector<string> equation_vec=equation_string_to_equation_vector(replace);
  string value1=equation_vec[0];
  string value2=equation_vec[2];
  string math_op=equation_vec[1];

  replace=get_math_operator2(value1, value2, math_op);
  equation[indice]=replace;
  return equation;
}

string get_value_for_replace_whole_equation(const string compartment_name_split, const vector<string> params)
{
  int j=0;
  int indice;
  string result;

  for(const auto &i: global_compartment_names)
    {
      if(compartment_name_split==i)
	{
	  indice=j;
	  break;
	}
      j++;
    }

  result=params[indice];
  return result;
}

vector<string> replace_in_whole_equation(vector<string> equation, const vector<int> indices, const vector<string> params, const SplittedStrings param_data)
{
  int j=0;
  int indice;
  SplittedString string_splitted;
  string compartment_name_split;
  string value;
  string repl;
  string eq_params_i;
  vector<SplittedString> eq_params=param_data[param_data_i];
  string compartment_name;
  string initial_value_name;

  for(const auto&i: eq_params)
    {
      indice=indices[j];
      compartment_name_split=i.splitted_string_part1;
      repl=get_value_for_replace_whole_equation(compartment_name_split, params);
      equation=replace_in_equation(equation, indice, repl);
      j++;
    }
  param_data_i++;
  return equation;
}

vector<string> values_to_add_update(vector<string> values_to_add, const string constant)
{
  int j=0;
  double result;
  double constant_double=stod(constant);
  double values_to_add_i_double;
  const string zero="0";
  string result_str;
  string values_to_add_i;

  if(constant!=zero)
    {
      for(auto const&i: values_to_add)
	{
	  values_to_add_i_double=stod(i);
	  result=constant_double*values_to_add_i_double;
	  result_str=to_string(result);
	  values_to_add[j]=result_str;
	  j++;
	}
    }
  return values_to_add;
}
