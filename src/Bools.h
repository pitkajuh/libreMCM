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

#include <map>
#include "IsIn.h"

using std::map;

struct Bools
{
public:
  bool variable=0;
  bool constant=0;
  bool numeric=0;
  bool math=0;

  Bools(const string &s1, const vector<string> &variables, const map<string, uint16_t> &constants)
  {
    variable=IsIn(s1, variables);
    constant=constants.find(s1)!=constants.end();
    math=(s1.substr(0, 1)=="@")?1:0;

    if(!variable and !constant and !math) numeric=1;
  }
};

#endif
