/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef COMPARTMENTEQUATIONSADDSUBTRACTALL_H
#define COMPARTMENTEQUATIONSADDSUBTRACTALL_H

#include "CompartmentEquationsAddSubtract.h"

class CompartmentEquationsAddSubtractAll
{
 public:
  vector<CompartmentEquationsAddSubtract> equations_all;

  void push_back(const CompartmentEquationsAddSubtract equation_add_subtract)
  {
    equations_all.push_back(equation_add_subtract);
  }
  void clear()
  {
    equations_all.clear();
  }
  int size()
  {
    int size=equations_all.size();
    return size;
  }
  CompartmentEquationsAddSubtract& operator[](const int i)
  {
    return equations_all[i];
  }
  const CompartmentEquationsAddSubtract& operator[](const int i) const
  {
    return equations_all[i];
  }
};

#endif
