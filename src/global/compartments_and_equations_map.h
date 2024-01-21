/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef COMPARTMENTSANDEQUATIONSMAP_H
#define COMPARTMENTSANDEQUATIONSMAP_H

#include <unordered_map>
#include "../class/EquationNamesAddSubtract.h"

using std::unordered_map;

extern unordered_map<string, EquationNamesAddSubtract> compartments_and_equations;

#endif
