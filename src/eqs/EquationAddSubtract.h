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

#include "../inc/namespace.h"
#include "../types/Csv.h"
#include "../types/AddSubtract.h"

using namespace libremcm;

map<string, AddSubtract> EquationAddSubtract(const Csv &csv);

#endif
