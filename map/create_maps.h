/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef CREATEMAPS_H
#define CREATEMAPS_H

#include <map>
#include "../class/TargetCompartments.h"

using std::map;

extern map<string, vector<string>> parameter_map;
extern map<string, vector<string>> compartment_map_v2;
extern map<string, map<string, vector<string>>> compartment_map;
extern map<string, TargetCompartments> compartment_target_map;
void create_compartment_map();

#endif
