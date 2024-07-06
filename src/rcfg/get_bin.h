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
#include "../inc/namespace.h"

using namespace libremcm;
using InitialValues=smap;

Pair GetData(ifstream &bin, streampos &from);
FileData Read(ifstream &bin, streampos &from);
smap GetBin(ifstream &bin, streampos *from, string *name=nullptr);
map<string, InitialValues> GetInitialValues(ifstream &bin);
smap GetMap(ifstream &bin, streampos *from=nullptr);

#endif
