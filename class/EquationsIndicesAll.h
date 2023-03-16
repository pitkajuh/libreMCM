/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef EQUATIONSINDICESALL_H
#define EQUATIONSINDICESALL_H

#include "EquationsIndices.h"

class EquationsIndicesAll
{
 public:
  vector<EquationsIndices> equations;

  void push_back(const EquationsIndices equation)
  {
    equations.push_back(equation);
  }
  void clear()
  {
    equations.clear();
  }
  int size()
  {
    int size=equations.size();
    return size;
  }
  EquationsIndices& operator[](const int i)
  {
    return equations[i];
  }
  const EquationsIndices& operator[](const int i) const
  {
    return equations[i];
  }
};

#endif
