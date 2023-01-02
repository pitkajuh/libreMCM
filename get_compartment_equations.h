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
#include "read_bin.h"
#include "read_compartment_definition.h"
#include "read_compartment.h"
#include "calculate_helpers.h"

using namespace std;

extern vector<tuple<string, vector<string>, vector<string>>> all_calculation_rules;
string get_eq_corresponding_to_eq_name(string eq_name);
vector<string> get_equations_from_compartment_csv(vector<vector<string>> compartment_vector, int i_start, int j_start, bool get_horizontal);
tuple<string, vector<string>, vector<string>> get_equations_compartment(vector<vector<string>> compartment_vector, string compartment, int i_start, int j_start);
tuple<vector<string>, int> get_target_compartments(string compartment_name, bool add_or_not, int i_start);
