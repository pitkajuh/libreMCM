/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <fstream>
#include <vector>

using namespace std;

vector<string> is_variable_helper(string line);
bool is_variable(string fchar);
bool is_string_numerical_value(string constant);
string get_math_operator(string value1_input, string value2_input, string math_operator);
string calculate_order_of_operations(vector<string> fa);
