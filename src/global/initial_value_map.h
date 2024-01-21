/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef INITIALVALUEMAP_H
#define INITIALVALUEMAP_H

#include <unordered_map>
#include "../class/SplittedString.h"

using std::unordered_map;

extern unordered_map<string, SplittedString> initial_value_map;

#endif
