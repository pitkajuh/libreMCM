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

#include "../types/Csv.h"
#include "../types/AddSubtract.h"
#include <unordered_map>

unordered_map<string, AddSubtract> EquationAddSubtract(const Csv &csv);

#endif
