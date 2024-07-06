/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef PARSEINITIALVALUES_H
#define PARSEINITIALVALUES_H

#include <vector>
#include "../inc/namespace.h"

using namespace libremcm;
using std::vector;
using InitialValues=SMap;
using DInitialValues=Map<string, double>;

Map<string, DInitialValues> ParseInitialValues(Map<string, InitialValues> &ivs, const vector<string> &iv_names);

#endif
