/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef MAPUTILS_H
#define MAPUTILS_H

#include <unordered_map>

using std::unordered_map;

unordered_map<string, string> CreatePairMap(Pair pair);

#endif
