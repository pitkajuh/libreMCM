/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <cmath>
#include "../global/global_constants.h"

using std::to_string;

string get_math_operator2(const string value1_input, const string value2_input, const string math_operator)
{
  const double value1_input_double=stod(value1_input);
  const double value2_input_double=stod(value2_input);
  double result_double;
  string result;

  if(math_operator==MULTIPLY)
    {
      result_double=value1_input_double*value2_input_double;
    }
  else if(math_operator==ADD)
    {
      result_double=value1_input_double+value2_input_double;
    }
  else if(math_operator==DIVIDE)
    {
      result_double=value1_input_double/value2_input_double;
    }
  else if(math_operator==SUBTRACT)
    {
      result_double=value1_input_double-value2_input_double;
    }
  else if(math_operator==POWER)
    {
      result_double=pow(value1_input_double, value2_input_double);
    }
  result=to_string(result_double);
  return result;
}
