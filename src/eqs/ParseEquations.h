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

#include "../types/MathOperation.h"
#include "../inc/namespace.h"

using namespace libremcm;
using MathOperations=Map<string, OpTmp>;

Map<string, MathOperations> ParseEquations(const SMap &equations_map);
vector<string> GetParenthesis(const vector<string> &equation, const int &open, const int &close, unsigned int &k, MathOperations &ooo);
vector<string> RemoveOpenClose(vector<string> equation);

#endif
