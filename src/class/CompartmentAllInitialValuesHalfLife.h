/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef COMPARTMENTALLINITIALVALUESHALFLIFE_H
#define COMPARTMENTALLINITIALVALUESHALFLIFE_H

#include "AllInitialValuesHalfLife.h"

class CompartmentAllInitialValuesHalfLife
{
 public:
  string compartment;
  AllInitialValuesHalfLife initial_values;
};

#endif
