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
#include <string>
#include "../types/MathOperation.h"

using std::unordered_map;
using std::string;

void ParseEquations(const unordered_map<string, string> &equations_map);
vector<string> GetParenthesis(const vector<string> &equation, const int &open, const int &close, unsigned int &k, vector<OpTmp> &ooo);
vector<string> RemoveOpenClose(vector<string> equation);

#endif
