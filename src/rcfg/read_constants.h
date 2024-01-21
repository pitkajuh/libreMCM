/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef READCONSTANTS_H
#define READCONSTANTS_H

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

void read_constants(const string line, const unordered_map<string, string> specific_values);

#endif
