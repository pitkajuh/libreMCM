/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef COMPARTMENTTARGETMAP_H
#define COMPARTMENTTARGETMAP_H

#include <map>
#include "../class/TargetCompartments.h"

using std::map;

extern map<string, TargetCompartments> compartment_target_map;

#endif
