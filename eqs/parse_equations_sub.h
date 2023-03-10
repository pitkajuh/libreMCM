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

EquationsAddSubtract replace_param_eq(vector<string> equation_vector, bool equation_add, string compartment_name, int compartment_start_index, int index1);

#endif
