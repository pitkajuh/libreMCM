/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef INITIALVALUES_H
#define INITIALVALUES_H

#include <vector>
#include "InitialValue.h"

using std::vector;

class InitialValues
{
 public:
  vector<InitialValue> initial_values;

  void push_back(const InitialValue initial_value)
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
  InitialValue& operator[](const int i)
  {
    return initial_values[i];
  }
  const InitialValue& operator[](const int i) const
  {
    return initial_values[i];
  }
};

#endif
