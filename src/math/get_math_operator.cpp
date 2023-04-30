/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <sstream>
#include <cmath>
#include "../global/global_constants.h"
#include "is_variable.h"

using std::ostringstream;

string get_math_operator(const string value1, const string value2, const string math_operator)
{
  ostringstream res;
  string result;
  double result_double;
  const bool is_value1_variable=is_variable(value1);
  const bool is_value2_variable=is_variable(value2);

  if(is_value1_variable or is_value2_variable)
    {
      result=value1+math_operator+value2;
    }
  else
    {
      double value1_double=value1_double=stod(value1);
      double value2_double=value2_double=stod(value2);

      if(math_operator==MULTIPLY)
	{
	  result_double=value1_double*value2_double;
	}
      else if(math_operator==ADD)
	{
	  result_double=value1_double+value2_double;
	}
      else if(math_operator==DIVIDE)
	{
	  result_double=value1_double/value2_double;
	}
    }
  res<<result_double;
  result=res.str();
  return result;
}

string get_math_operator2(const string value1, const string value2, const string math_operator)
{
  ostringstream res;
  const double value1_double=stod(value1);
  const double value2_double=stod(value2);
  double result_double;
  string result;

  if(math_operator==MULTIPLY)
    {
      result_double=value1_double*value2_double;
    }
  else if(math_operator==ADD)
    {
      result_double=value1_double+value2_double;
    }
  else if(math_operator==DIVIDE)
    {
      result_double=value1_double/value2_double;
    }
  res<<result_double;
  result=res.str();
  return result;
}
