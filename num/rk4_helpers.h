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

extern int param_data_i;
vector<string> replace_in_equation(vector<string> equation, const int indice, const string k_add);
vector<string> replace_in_whole_equation(vector<string> equation, const vector<int> indices, const vector<string> params, const SplittedStrings param_data);
vector<string> get_multiple_last_values(const vector<SplittedString> vec);
vector<string> values_to_add_update(vector<string> values_to_add, const string constant);

#endif
