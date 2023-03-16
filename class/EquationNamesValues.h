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

  void push_back(const EquationName equation)
  {
    equations.push_back(equation);
  }
  void clear()
  {
    equations.clear();
  }
  EquationName& operator[](const int i)
  {
    return equations[i];
  }
  const EquationName& operator[](const int i) const
  {
    return equations[i];
  }
};

#endif
