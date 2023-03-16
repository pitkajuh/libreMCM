/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef EQUATIONSALL_H
#define EQUATIONSALL_H

#include "Equations.h"

class EquationsAll
{
 public:
  vector<Equations> equations;

  void push_back(const Equations equation)
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
  Equations& operator[](const int i)
  {
    return equations[i];
  }
  const Equations& operator[](const int i) const
  {
    return equations[i];
  }
};

#endif
