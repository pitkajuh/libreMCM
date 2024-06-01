/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef GETBIN_H
#define GETBIN_H

#include "../types/ReadFile.h"

Pair GetData(ifstream &bin, streampos from);
FileData Read(ifstream &bin, streampos from);

#endif
