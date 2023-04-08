/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../class/SplittedStrings.h"
#include "../global/global_constants.h"
#include "../global/compartment_diagonal_v2.h"
#include "../global/compartment_map.h"
#include "../math/get_math_operator_v2.h"
#include "../util/get_compartment_index.h"

using std::to_string;

const vector<string> replace_in_equation(vector<string> equation, const int indice, const string k_add)
{
  const string fchar=equation[indice];
  const string replace=get_math_operator2(fchar, k_add, ADD);
  equation[indice]=replace;

  return equation;
}

const string get_value(const string compartment_name, const vector<string> params)
{
  const int i=get_compartment_index(compartment_name);
  const string result=params[i];
  return result;
}

const vector<string> replace_in_whole_equation(vector<string> equation, const vector<int> indices, const vector<string> params, const SplittedStrings param_data, const int indice_i)
{
  int j=0;
  int indice;
  bool is_negative;
  string replace;
  string compartment_name;
  const vector<SplittedString> eq_params=param_data[indice_i];

  for(const auto&i: eq_params)
    {
      indice=indices[j];
      compartment_name=i.splitted_string_part1;
      replace=get_value(compartment_name, params);
      equation=replace_in_equation(equation, indice, replace);
      j++;
    }
  return equation;
}

const vector<string> values_to_add_update(vector<string> values_to_add, const string constant)
{
  int j=0;
  double result;
  double values_to_add_i_double;
  const double constant_double=stod(constant);
  string result_str;
  string values_to_add_i;

  if(constant!=ZERO)
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
