/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

using namespace std;

extern int asd, comp;
tuple<vector<string>, vector<int>, vector<string>> combine_equations_and_indices(vector<tuple<vector<string>, vector<int>, bool, vector<string>>> vector1);
vector<string> replace_in_equation(vector<string> equation, int indices, string k_add);
vector<string> replace_in_whole_equation (vector<string> equation, vector<int> indices, vector<string> params, string addition, vector<vector<string>> param_data);
bool is_in_indices(int index, vector<int> indices);
vector<string> combine_string_vectors (vector<string> combine1, vector<string> combine2);
vector<int> combine_int_vectors (vector<int> combine1, vector<int> combine2);
vector<string> get_multiple_last_values (vector<string> vec);
tuple<vector<string>, vector<int>> parse_values_numerical(vector<string> parameter_data_for_indices, vector<int> indices);
double k_test(vector<string> equation, vector<int> indices, vector<string> values_to_add, string constant, vector<vector<string>> param_data, vector<int> numerical_calculation_order_of_operations);
