/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef ALLINITIALVALUES_H
#define ALLINITIALVALUES_H

#include "InitialValues.h"

class AllInitialValues
{
 public:
  vector<InitialValues> initial_values;

  void push_back(InitialValues initial_value)
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
  InitialValues get(int i)
  {
    InitialValues result=initial_values[i];
    return result;
  }
  void replace(InitialValues initial_value, int i)
  {
    initial_values[i]=initial_value;
  }
};

#endif
