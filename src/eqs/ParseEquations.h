/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef PARSEQUATIONS_H
#define PARSEQUATIONS_H

#include "../types/Data.h"
#include "../types/Equation.h"
#include "../types/MathOperation.h"

void ParseEquations(const SMap &equations_map, const Data &data);
vector<string> GetParenthesis(const vector<string> &equation, const uint8_t open, const uint8_t close, uint8_t &k, const Data &data, Equation *&e, Equation *&next);
vector<string> RemoveOpenClose(vector<string> equation);

#endif
