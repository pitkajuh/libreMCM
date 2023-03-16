/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef PARSEEQUATIONSSUB_H
#define PARSEEQUATIONSSUB_H

#include "../class/EquationsAddSubtract.h"

EquationsAddSubtract replace_param_eq(const vector<string> equation_vector, const bool equation_add, const string compartment_name);

#endif
