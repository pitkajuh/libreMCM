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

#include <map>
#include "../class/EquationNamesAddSubtract.h"

using std::map;

extern map<string, EquationNamesAddSubtract> compartments_and_equations;

#endif
