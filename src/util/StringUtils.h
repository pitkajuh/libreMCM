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

#include "../types/StringSplit.h"

const string ParseLine(string &line);
StringSplit LineSplit(const string &line);

#endif
