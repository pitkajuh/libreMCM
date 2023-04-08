/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef K_H
#define K_H

#include "../class/VecVecInt.h"
#include "../class/SplittedStrings.h"
#include "../class/Equations.h"

const string order_of_operations(vector<string> equation, const vector<int> math_op_ind);
const double k_subroutine(vector<string> equation, const vector<int> indices, vector<string> values_to_add, const string constant, const SplittedStrings param_data, const vector<int> numerical_calculation_order_of_operations);
const vector<string> k(Equations equations, const VecVecInt indices, const vector<string> values_to_add, const string constant, const SplittedStrings param_data, const VecVecInt numerical_calculation_order_of_operations);

#endif
