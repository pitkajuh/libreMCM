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

  void push_back(Equations equation)
  {
    equations.push_back(equation);
  }
  void clear()
  {
    equations.clear();
  }
  int get_size()
  {
    int size=equations.size();
    return size;
  }
  Equations get(int i)
  {
    Equations result=equations[i];
    return result;
  }
  void replace(Equations equation, int i)
  {
    equations[i]=equation;
  }
};

#endif
