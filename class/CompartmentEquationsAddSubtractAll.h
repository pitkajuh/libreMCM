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

  void push_back(CompartmentEquationsAddSubtract equation_add_subtract)
  {
    equations_all.push_back(equation_add_subtract);
  }
  void clear()
  {
    equations_all.clear();
  }
  int get_size()
  {
    int size=equations_all.size();
    return size;
  }
  CompartmentEquationsAddSubtract get(int i)
  {
    CompartmentEquationsAddSubtract result=equations_all[i];
    return result;
  }
};

#endif
