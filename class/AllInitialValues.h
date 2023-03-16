/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef ALLINITIALVALUES_H
#define ALLINITIALVALUES_H

#include "InitialValues.h"

class AllInitialValues
{
 public:
  vector<InitialValues> initial_values;

  void push_back(const InitialValues initial_value)
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
  InitialValues& operator[](const int i)
  {
    return initial_values[i];
  }
  const InitialValues& operator[](const int i) const
  {
    return initial_values[i];
  }
};

#endif
