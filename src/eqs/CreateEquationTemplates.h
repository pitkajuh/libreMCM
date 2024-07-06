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
using MathOperations=map<string, OpTmp>;

void CreateEquationTemplates(const map<string, MathOperations> &equations_map, const Csv &csv, smap &constants_map);

#endif
