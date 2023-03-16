/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef NOCOMPARTMENTINITIALVALUESHALFLIFE_H
#define NOCOMPARTMENTINITIALVALUESHALFLIFE_H

#include "InitialValuesHalfLife.h"

class NoCompartmentInitialValuesHalfLife
{
 public:
  vector<InitialValuesHalfLife> initial_values;

  void push_back(const InitialValuesHalfLife initial_value)
  {
    initial_values.push_back(initial_value);
  }
  void clear()
  {
    initial_values.clear();
  }
  InitialValuesHalfLife& operator[](const int i)
  {
    return initial_values[i];
  }
  const InitialValuesHalfLife& operator[](const int i) const
  {
    return initial_values[i];
  }
};

#endif
