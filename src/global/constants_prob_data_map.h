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
#include <map>

using std::string;
using std::map;

#include "../class/ConstantProbabilisticData.h"

extern map<string, ConstantProbabilisticData> constants_prob_data_map;

#endif
