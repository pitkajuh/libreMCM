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

  void push_back(EquationsAddSubtract equation)
  {
    vector_all.push_back(equation);
  }
  void clear()
  {
    vector_all.clear();
  }
  int get_size()
  {
    int size=vector_all.size();
    return size;
  }
  EquationsAddSubtract get(int i)
  {
    EquationsAddSubtract result=vector_all[i];
    return result;
  }
  void replace(EquationsAddSubtract equation, int i)
  {
    vector_all[i]=equation;
  }
};

#endif
