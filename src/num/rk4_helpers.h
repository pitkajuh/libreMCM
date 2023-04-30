/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef RK4HELPERS_H
#define RK4HELPERS_H

#include "../class/SplittedStrings.h"

const string get_value(const string compartment_name, const vector<string> params);
const vector<string> replace_in_whole_equation(vector<string> equation, const vector<int> indices, const vector<string> params, const SplittedStrings param_data, const int indice_i);

#endif
