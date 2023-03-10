/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef VECVECSTRING_H
#define VECVECSTRING_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class VecVecString
{
 public:
  vector<vector<string>> vec;

  int get_size()
  {
    int size=vec.size();
    return size;
  }
  vector<string> get(int i)
  {
    vector<string> result=vec[i];
    return result;
  }
  void push_back(vector<string> vec1)
  {
    vec.push_back(vec1);
  }
  void replace(vector<string> str, int i)
  {
    vec[i]=str;
  }
  void clear()
  {
    vec.clear();
  }
};

#endif
