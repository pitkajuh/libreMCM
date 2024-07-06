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
#include "../types/Csv.h"
#include "../inc/namespace.h"

using namespace libremcm;
using MathOperations=Map<string, OpTmp>;

void CreateEquationTemplates(const Map<string, MathOperations> &equations_Map, const Csv &csv, SMap &constants_Map);

#endif
