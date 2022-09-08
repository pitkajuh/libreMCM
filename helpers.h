#include <iostream>
#include <stdlib.h>
#include <tuple>
#include <cmath>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <assert.h>
#include <regex>
/* #include "global.h" */

using namespace std;

void calculation_done_function(vector<string> fa, int operator_indice);
void replace_in_vector(vector<string> fa, double result, int operator_indice);
vector<string> get_values_from_vector(vector<string> get_values_from, int indice_from, int indice_to);
tuple<string, double> read_variables(string line);
double get_variable_value (string variable);
bool is_string_numerical_value (string variable);
double is_number_or_variable (string ab);
double get_math_operator (string value11, string value22, string math_operator);
bool is_operator (string elem);
bool skip_indice_or_not (int indice, vector<int> indices_to_skip);
