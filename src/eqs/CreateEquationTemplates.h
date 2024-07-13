/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef CREATEEQUATIONTEMPLATES_H
#define CREATEEQUATIONTEMPLATES_H

#include "../types/MathOperation.h"
#include "../types/Data.h"

using MathOperations=Map<string, MathOperation>;

void CreateEquationTemplates(const Map<string, MathOperations> &equations_map, const Data &data);

#endif
