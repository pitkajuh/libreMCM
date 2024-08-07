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
#include "../types/MathOperation.h"

void ParseEquations(const SMap &equations_map, const Data &data);
vector<string> GetParenthesis(const vector<string> &equation, const int &open, const int &close, unsigned int &k, const Data &data, MathOperation *&e, MathOperation *&next);
vector<string> RemoveOpenClose(vector<string> equation);

#endif
