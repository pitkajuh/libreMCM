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

#include <unordered_map>
#include "../class/TargetCompartments.h"

using std::unordered_map;

extern unordered_map<string, TargetCompartments> compartment_target_map;

#endif
