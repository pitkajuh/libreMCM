/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef GETCOMPARTMENT_H
#define GETCOMPARTMENT_H

#include <fstream>
#include "../types/Csv.h"

using std::ifstream;

const Csv GetCompartment(ifstream &f);

#endif
