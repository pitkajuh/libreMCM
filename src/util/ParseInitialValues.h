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
using InitialValues=smap;
using DInitialValues=map<string, double>;

map<string, DInitialValues> ParseInitialValues(map<string, InitialValues> &ivs, const vector<string> &iv_names);

#endif
