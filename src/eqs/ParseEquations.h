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

using std::unordered_map;
using std::string;

void ParseEquations(const unordered_map<string, string> equations_map);
vector<string> GetParenthesis(vector<string> equation, const int open, const int close);
vector<string> RemoveOpenClose(vector<string> equation);

#endif
