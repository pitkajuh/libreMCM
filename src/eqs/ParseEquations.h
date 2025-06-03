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

map<string, GraphEquation*> ParseEquations(const map<string, vector<string>> &equations_map, const vector<string> &data);
vector<string> GetParenthesis(const vector<string> &equation, const uint8_t open, const uint8_t close, uint8_t &k, const vector<string> &data, GraphEquation *&graph);
vector<string> RemoveOpenClose(vector<string> equation);

#endif
