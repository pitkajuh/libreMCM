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

  void push_back(InitialValuesHalfLife initial_value)
  {
    initial_values.push_back(initial_value);
  }
  void clear()
  {
    initial_values.clear();
  }
  int get_size()
  {
    int size=initial_values.size();
    return size;
  }
  InitialValuesHalfLife get(int i)
  {
    InitialValuesHalfLife result=initial_values[i];
    return result;
  }
  void replace(InitialValuesHalfLife initial_value, int i)
  {
    initial_values[i]=initial_value;
  }
};

#endif
