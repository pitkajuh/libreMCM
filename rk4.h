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

using namespace std;

vector<tuple<string, tuple<vector<string>, vector<int>, vector<string>>, vector<int>, vector<string>, vector<string>>> solution_prepare(string compartment_name, vector<vector<string>> equations_add_all, vector<vector<string>> equations_subtract_all);
vector<string> k_calc(vector<vector<string>> equations, vector<vector<int>> indices, vector<string> values_to_add, string constant, vector<vector<string>> param_data, vector<vector<int>> numerical_calculation_order_of_operations);
extern vector<string> global_compartment_names;
