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
#include <fstream>
#include <vector>

using namespace std;

extern vector<tuple<string, vector<vector<tuple<string, string, int>>>>> compartment_parameters_rt;
string get_compartment_parameter_value(string parameter_wanted);
tuple<string, string> get_compartment_parameter_value_subroutine(string parameter_wanted);
