/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef READCOMPARTMENT_H
#define READCOMPARTMENT_H

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

void get_compartments(string directory);
extern vector<string> compartment_diagonal;
extern vector<string> compartment_diagonal_v2;
extern map<int, vector<string>> row_map;
extern map<int, vector<string>> column_map;

#endif
