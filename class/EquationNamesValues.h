/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef EQUATIONNAMESVALUES_H
#define EQUATIONNAMESVALUES_H

#include "EquationName.h"

class EquationNamesValues
{
 public:
  vector<EquationName> equations;

  void push_back(EquationName equation)
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
  EquationName get(int i)
  {
    EquationName result=equations[i];
    return result;
  }
};

#endif
