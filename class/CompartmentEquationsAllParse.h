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

  void push_back(const CompartmentEquationsAll equation)
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
  CompartmentEquationsAll& operator[](const int i)
  {
    return vector_all[i];
  }
  const CompartmentEquationsAll& operator[](const int i) const
  {
    return vector_all[i];
  }
};

#endif
