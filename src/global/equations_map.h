/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef EQUATIONSMAP_H
#define EQUATIONSMAP_H

#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

// Contains equation name (e.g. f(x)) as string and its value as vector (e.g. {"a", "*", "x"}).

extern map<string, vector<string>> equations_map;

#endif
