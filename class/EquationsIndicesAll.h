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

  void push_back(EquationsIndices equation)
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
  EquationsIndices get(int i)
  {
    EquationsIndices result=equations[i];
    return result;
  }
  void replace(EquationsIndices equation, int i)
  {
    equations[i]=equation;
  }
};

#endif
