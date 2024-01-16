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
#include "../math/get_math_operator.h"
#include "../util/get_compartment_index.h"

using std::to_string;

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
  double val1;
  double val2;
  string compartment_name;
  const vector<SplittedString> eq_params=param_data[indice_i];

  for(const auto&i: eq_params)
    {
      indice=indices[j];
      compartment_name=i.splitted_string_part1;
      val1=stod(equation[indice]);
      val2=stod(get_value(compartment_name, params));
      val1=val1+val2;
      equation[indice]=to_string(val1);
      j++;
    }
  return equation;
}
