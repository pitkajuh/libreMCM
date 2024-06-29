/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef ISIN_H
#define ISIN_H

#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;

bool IsNumerical(const string &s);
bool IsIn(const string &s, const unordered_map<string, string> &f);
bool IsIn(const string &s, const vector<string> &f);

#endif
