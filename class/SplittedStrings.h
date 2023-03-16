/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef SPLITTEDSTRINGS_H
#define SPLITTEDSTRINGS_H

#include <vector>
#include "SplittedString.h"

using std::vector;

class SplittedStrings
{
 public:
  vector<vector<SplittedString>> vec;

  void push_back(const vector<SplittedString> vec1)
  {
    vec.push_back(vec1);
  }
  vector<SplittedString>& operator[](const int i)
  {
    return vec[i];
  }
  const vector<SplittedString>& operator[](const int i) const
  {
    return vec[i];
  }
  void clear()
  {
    vec.clear();
  }
  int size()
  {
    int size=vec.size();
    return size;
  }
};

#endif
