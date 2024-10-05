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
using InitialValues=SMap;

const Pair GetData(ifstream &bin, streampos &from);
const FileData Read(ifstream &bin, streampos &from);
const SMap GetBin(ifstream &bin, streampos *from, string *name=nullptr);
const Map<string, InitialValues> GetInitialValues(ifstream &bin);
const SMap GetMap(ifstream &bin, streampos *from=nullptr);

#endif
