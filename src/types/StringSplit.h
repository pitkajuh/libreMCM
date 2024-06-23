/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef STRINGSPLIT_H
#define STRINGSPLIT_H

#include <string>

using std::string;

struct StringSplit
{
  string name;
  string value;

  StringSplit(){}
  StringSplit(const string &s1, const string &s2)
  {
    name=s1;
    value=s2;
  }
};

#endif
