/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef READBIN_H
#define READBIN_H

#include <map>
#include "../class/Constants.h"
#include "../class/EquationNamesValues.h"

using std::map;

extern EquationNamesValues equations;
extern map<string, vector<string>> equations_map;
extern Constants constants;
void read_bin(const string directory);

#endif
