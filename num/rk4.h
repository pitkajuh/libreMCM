/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef RK4_H
#define RK4_H

#include "../class/Equations.h"
#include "../class/Solution.h"
#include "../class/VecVecInt.h"
#include "../class/SplittedStrings.h"

vector<Solution> solution_prepare(const string compartment_name, Equations equations_add_all, Equations equations_subtract_all);
vector<string> k(const Equations equations, const VecVecInt indices, const vector<string> values_to_add, const string constant, const SplittedStrings param_data, const VecVecInt numerical_calculation_order_of_operations);
double k_subroutine(vector<string> equation, const vector<int> indices, vector<string> values_to_add, const string constant, const SplittedStrings param_data, const vector<int> numerical_calculation_order_of_operations);
extern vector<string> global_compartment_names;

#endif
