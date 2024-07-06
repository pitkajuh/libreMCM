/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef COMPARTMENT_H
#define COMPARTMENT_H

#include "../inc/namespace.h"

using namespace libremcm;
using InitialValues=SMap;

class Compartment
{
public:
  vector<string> equations_add;
  vector<string> equations_subtract;
  InitialValues ivs;
};

#endif
