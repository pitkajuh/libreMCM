/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>
#include "ConstantNameAndValue.h"

using std::vector;

class Constants
{
 public:
  vector<ConstantNameAndValue> constants;

  void push_back(ConstantNameAndValue constant)
  {
    constants.push_back(constant);
  }
  void clear()
  {
    constants.clear();
  }
  int get_size()
  {
    int size=constants.size();
    return size;
  }
  ConstantNameAndValue get(int i)
  {
    ConstantNameAndValue result=constants[i];
    return result;
  }
};

#endif
