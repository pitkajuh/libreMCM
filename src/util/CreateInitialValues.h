/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef CREATEINITIALVALUES_H
#define CREATEINITIALVALUES_H

#include <vector>
#include "../inc/namespace.h"

using namespace libremcm;
using std::vector;

const vector<string> CreateAllInitialValues(const Map<string, InitialValues> &iv);

#endif
