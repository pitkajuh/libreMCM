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

#include <unordered_map>
#include "../types/MathOperation.h"

using std::unordered_map;
using MathOperations=vector<OpTmp>;

unordered_map<string, MathOperations> ParseEquations(const unordered_map<string, string> &equations_map);
vector<string> GetParenthesis(const vector<string> &equation, const int &open, const int &close, unsigned int &k, MathOperations &ooo);
vector<string> RemoveOpenClose(vector<string> equation);

#endif
