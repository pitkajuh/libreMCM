/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef INITIALVALUESHALFLIFE_H
#define INITIALVALUESHALFLIFE_H

#include <vector>
#include "InitialValueHalfLife.h"

using std::vector;

class InitialValuesHalfLife
{
 public:
  vector<InitialValueHalfLife> initial_values;

  void push_back(const InitialValueHalfLife initial_value)
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
  InitialValueHalfLife& operator[](const int i)
  {
    return initial_values[i];
  }
  const InitialValueHalfLife& operator[](const int i) const
  {
    return initial_values[i];
  }
};

#endif
