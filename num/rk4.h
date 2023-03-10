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
#include "../class/VecVecString.h"

vector<Solution> solution_prepare(string compartment_name, Equations equations_add_all, Equations equations_subtract_all);
vector<string> k(Equations equations, VecVecInt indices, vector<string> values_to_add, string constant, VecVecString param_data, VecVecInt numerical_calculation_order_of_operations);
double k_subroutine(vector<string> equation, vector<int> indices, vector<string> values_to_add, string constant, vector<vector<string>> param_data, vector<int> numerical_calculation_order_of_operations);
extern vector<string> global_compartment_names;

#endif
