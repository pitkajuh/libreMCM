/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <string>
#include "../types/StringSplit.h"

using std::string;

const string ParseLine(string line);
StringSplit LineSplit(string line);

#endif
