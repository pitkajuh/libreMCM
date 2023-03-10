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

#include "../class/VecVecString.h"

extern int param_data_i;
vector<string> replace_in_equation(vector<string> equation, int indices, string k_add);
vector<string> replace_in_whole_equation(vector<string> equation, vector<int> indices, vector<string> params, string addition, VecVecString param_data);
vector<string> get_multiple_last_values(vector<string> vec);
vector<string> values_to_add_update(vector<string> values_to_add, string constant);

#endif
