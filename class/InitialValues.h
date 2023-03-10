/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef INITIALVALUES_H
#define INITIALVALUES_H

#include <vector>
#include "InitialValue.h"

using std::vector;

class InitialValues
{
 public:
  vector<InitialValue> initial_values;

  void push_back(InitialValue initial_value)
  {
    initial_values.push_back(initial_value);
  }
  void clear()
  {
    initial_values.clear();
  }
  int get_size()
  {
    int size=initial_values.size();
    return size;
  }
  InitialValue get(int i)
  {
    InitialValue result=initial_values[i];
    return result;
  }
  void replace(InitialValue initial_value, int i)
  {
    initial_values[i]=initial_value;
  }
};

#endif
