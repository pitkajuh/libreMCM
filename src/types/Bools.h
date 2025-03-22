/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef BOOLS_H
#define BOOLS_H

#include "../util/IsIn.h"

struct Bools
{
public:
  bool variable;
  bool constant;
  bool numeric;
  bool math;

  Bools(const string &s1, const vector<string> &data)
  {
    variable=IsIn(s1, data);
    numeric=IsNumerical(s1);
    math=(s1.substr(0, 1)=="@") ? 1 : 0;
    if(!variable and !numeric and !math) constant=1;
    else constant=0;
  }
};

#endif
