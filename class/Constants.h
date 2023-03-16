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

  void push_back(const ConstantNameAndValue constant)
  {
    constants.push_back(constant);
  }
  void clear()
  {
    constants.clear();
  }
  int size()
  {
    int size=constants.size();
    return size;
  }
  ConstantNameAndValue& operator[](const int i)
  {
    return constants[i];
  }
  const ConstantNameAndValue& operator[](const int i) const
  {
    return constants[i];
  }
};

#endif
