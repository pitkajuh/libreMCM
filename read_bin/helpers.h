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
// #include "read_variables.h"
// #include "global.h"

using namespace std;

void calculation_done_function(vector<string> fa, int operator_indice);
vector<string> replace_in_vector(vector<string> fa, string result, int index_replace_from, int index_replace_to);
vector<string> get_values_from_vector(vector<string> get_values_from, int indice_from, int indice_to);
tuple<string, double> read_constants(string line);
double get_constant_value (string constant);
bool is_string_numerical_value (string constant);
double is_number_or_constant (string ab);
double get_math_operator (string value11, string value22, string math_operator);
bool is_operator (string elem);
bool skip_indice_or_not (int indice, vector<int> indices_to_skip);
string line_commented_or_not(string line);
