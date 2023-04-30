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
#include <map>

using std::string;
using std::map;

void read_constants(const string line, map<string, string> specific_values);

#endif
