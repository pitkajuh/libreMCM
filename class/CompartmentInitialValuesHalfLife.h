/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef COMPARTMENTINITIALVALUESHALFLIFE_H
#define COMPARTMENTINITIALVALUESHALFLIFE_H

#include "InitialValuesHalfLife.h"

class CompartmentInitialValuesHalfLife
{
 public:
  string compartment;
  InitialValuesHalfLife initial_values;
};

#endif
