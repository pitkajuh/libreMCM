/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef ALLCOMPARTMENTALLINITIALVALUESHALFLIFE_H
#define ALLCOMPARTMENTALLINITIALVALUESHALFLIFE_H

#include "CompartmentAllInitialValuesHalfLife.h"

class AllCompartmentAllInitialValuesHalfLife
{
 public:
  vector<CompartmentAllInitialValuesHalfLife> initial_values;

  void push_back(const CompartmentAllInitialValuesHalfLife initial_value)
  {
    initial_values.push_back(initial_value);
  }
  void clear()
  {
    initial_values.clear();
  }
  int size()
  {
    int size=initial_values.size();
    return size;
  }
  CompartmentAllInitialValuesHalfLife& operator[](const int i)
  {
    return initial_values[i];
  }
  const CompartmentAllInitialValuesHalfLife& operator[](const int i) const
  {
    return initial_values[i];
  }
};

#endif
