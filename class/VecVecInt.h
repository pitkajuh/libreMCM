/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef VECVECINT_H
#define VECVECINT_H

#include <vector>

using std::vector;

class VecVecInt
{
 public:
  vector<vector<int>> vec;

  void push_back(const vector<int> vec1)
  {
    vec.push_back(vec1);
  }
  vector<int>& operator[](const int i)
  {
    return vec[i];
  }
  const vector<int>& operator[](const int i) const
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
