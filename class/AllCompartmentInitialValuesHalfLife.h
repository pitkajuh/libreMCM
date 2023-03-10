/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef ALLCOMPARTMENTINITIALVALUESHALFLIFE_H
#define ALLCOMPARTMENTINITIALVALUESHALFLIFE_H

#include "CompartmentAllInitialValuesHalfLife.h"

class AllCompartmentInitialValuesHalfLife
{
 public:
  vector<CompartmentAllInitialValuesHalfLife> initial_values;

  void push_back(CompartmentAllInitialValuesHalfLife initial_value)
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
  CompartmentAllInitialValuesHalfLife get(int i)
  {
    CompartmentAllInitialValuesHalfLife result=initial_values[i];
    return result;
  }
  void replace(CompartmentAllInitialValuesHalfLife initial_value, int i)
  {
    initial_values[i]=initial_value;
  }
};

#endif
