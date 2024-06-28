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

#include <unordered_map>
#include "../types/MathOperation.h"
#include "../types/Csv.h"

using std::unordered_map;
using MathOperations=vector<OpTmp>;

void CreateEquationTemplates(const unordered_map<string, MathOperations> &equations_map, const Csv &csv, const unordered_map<string, string> &constants_map);

#endif
