/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <iostream>

using namespace std;

void parse_compartment_eqs_for_num_calc();
extern vector<vector<string>> equations_add_all, equations_subtract_all;
extern vector<tuple<string, vector<vector<string>>, vector<vector<string>>>> final_equations_for_calculation;
