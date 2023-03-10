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

  void push_back(EquationParseData equation)
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
  EquationParseData get(int i)
  {
    EquationParseData result=equations[i];
    return result;
  }
  void replace(EquationParseData equation, int i)
  {
    equations[i]=equation;
  }
  void erase(int i)
  {
    equations.erase(equations.begin()+i);
  }
};

#endif
