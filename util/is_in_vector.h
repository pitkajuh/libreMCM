/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef ISINVECTORF_H
#define ISINVECTORF_H

#include <string>
#include <vector>
#include "../class/IsInVector.h"

using std::string;
using std::vector;

IsInVector is_in_vector(const vector<string> vec, const string str_find);

#endif
