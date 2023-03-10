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

  int get_size()
  {
    int size=vec.size();
    return size;
  }
  vector<int> get(int i)
  {
    vector<int> result=vec[i];
    return result;
  }
  void push_back(vector<int> vec1)
  {
    vec.push_back(vec1);
  }
  void replace(vector<int> str, int i)
  {
    vec[i]=str;
  }
  void clear()
  {
    vec.clear();
  }
};

#endif
