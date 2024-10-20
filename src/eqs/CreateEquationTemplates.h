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

void CreateEquationTemplates(const Data &data, const Map<string, Equation*> equationMap);

#endif
