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
#include "../global/global.h"
#include "is_variable.h"

using std::to_string;

string get_math_operator(string value1_input, string value2_input, string math_operator)
{
  string result;
  double result_double;
  bool is_value1_variable=is_variable(value1_input);
  bool is_value2_variable=is_variable(value2_input);

  if(is_value1_variable or is_value2_variable)
    {
      result=value1_input+math_operator+value2_input;
    }
  else
    {
      double value1_input_double=value1_input_double=stod(value1_input);
      double value2_input_double=value2_input_double=stod(value2_input);

      if(math_operator==multiply)
	{
	  result_double=value1_input_double*value2_input_double;
	}
      else if(math_operator==add)
	{
	  result_double=value1_input_double+value2_input_double;
	}
      else if(math_operator==divide)
	{
	  result_double=value1_input_double/value2_input_double;
	}
      else if(math_operator==subtract)
	{
	  result_double=value1_input_double-value2_input_double;
	}
      else if(math_operator==power)
	{
	  result_double=pow(value1_input_double, value2_input_double);
	}
    }
  result=to_string(result_double);
  return result;
}
