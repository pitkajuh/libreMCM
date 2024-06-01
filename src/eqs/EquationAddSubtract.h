/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef EQUATIONADDSUBTRACT_H
#define EQUATIONADDSUBTRACT_H

#include <unordered_map>
#include "../types/Csv.h"

using std::unordered_map;

void EquationAddSubtract(const unordered_map<string, string> equations_map, const Csv csv);

#endif
