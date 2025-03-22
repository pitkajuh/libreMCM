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

#include "../types/Equation.h"
#include "../types/MathOperation.h"
#include "../types/Graph.h"

Map<string, Equation*> ParseEquations(const SMap &equations_map, const vector<string> &data);
vector<string> GetParenthesis(const vector<string> &equation, const uint8_t open, const uint8_t close, uint8_t &k, const vector<string> &data, Equation *&e, Equation *&next, GraphEquation *&graph);
vector<string> RemoveOpenClose(vector<string> equation);

#endif
