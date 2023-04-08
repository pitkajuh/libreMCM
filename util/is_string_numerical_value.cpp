/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <string>
#include <regex>

using namespace std;

const bool is_string_numerical_value(const string constant)
{
  // Checks whether there are numbers(0-9) in the equations, not only constants and variables. Returns true, if string is a valid number.

  const string str="^(-?)(0|([1-9][0-9]*))(\\.[0-9]+)?$";
  const bool result=regex_match(constant, regex(str));
  return result;
}
