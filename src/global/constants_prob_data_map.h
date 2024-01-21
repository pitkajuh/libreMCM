/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef CONSTANTSPROBDATAMAP_H
#define CONSTANTSPROBDATAMAP_H

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

#include "../class/ConstantProbabilisticData.h"

extern unordered_map<string, ConstantProbabilisticData> constants_prob_data_map;

#endif
