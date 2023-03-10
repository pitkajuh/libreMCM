/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef COMPARTMENTEQUATIONSALLPARSE_H
#define COMPARTMENTEQUATIONSALLPARSE_H

#include <vector>
#include "CompartmentEquationsAll.h"

using std::vector;

class CompartmentEquationsAllParse
{
 public:
  vector<CompartmentEquationsAll> vector_all;

  void push_back(CompartmentEquationsAll equation)
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
  CompartmentEquationsAll get(int i)
  {
    CompartmentEquationsAll result=vector_all[i];
    return result;
  }
  void replace(CompartmentEquationsAll equation, int i)
  {
    vector_all[i]=equation;
  }
};

#endif
