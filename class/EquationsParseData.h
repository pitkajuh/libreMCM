/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef EQUATIONSPARSEDATA_H
#define EQUATIONSPARSEDATA_H

#include "EquationParseData.h"

class EquationsParseData
{
 public:
  vector<EquationParseData> equations;

  void push_back(const EquationParseData equation)
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
  EquationParseData& operator[](const int i)
  {
    return equations[i];
  }
  const EquationParseData& operator[](const int i) const
  {
    return equations[i];
  }
  void erase(const int i)
  {
    equations.erase(equations.begin()+i);
  }
};

#endif
