/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef EQUATIONSADDSUBTRACTALL_H
#define EQUATIONSADDSUBTRACTALL_H

#include "EquationsAddSubtract.h"

class EquationsAddSubtractAll
{
 public:
  vector<EquationsAddSubtract> vector_all;

  void push_back(const EquationsAddSubtract equation)
  {
    vector_all.push_back(equation);
  }
  void clear()
  {
    vector_all.clear();
  }
  int size()
  {
    int size=vector_all.size();
    return size;
  }
  EquationsAddSubtract& operator[](const int i)
  {
    return vector_all[i];
  }
  const EquationsAddSubtract& operator[](const int i) const
  {
    return vector_all[i];
  }
};

#endif
