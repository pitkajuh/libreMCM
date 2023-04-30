/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef COMPARTMENTMAP_H
#define COMPARTMENTMAP_H

#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

extern map<string, map<string, vector<string>>> compartment_map;

#endif
