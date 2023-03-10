/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef GETCOMPARTMENTEQUATIONS_H
#define GETCOMPARTMENTEQUATIONS_H

#include <map>
#include "../class/CompartmentEquationsAddSubtract.h"
#include "../class/EquationNamesAddSubtract.h"

using std::map;

extern map<string, EquationNamesAddSubtract> compartments_and_equations;
vector<string> get_eq_corresponding_to_eq_name(string eq_name);
CompartmentEquationsAddSubtract get_equations_compartment(string compartment);

#endif
