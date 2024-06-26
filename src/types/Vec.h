/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef VEC_H
#define VEC_H

#include <vector>

using std::vector;

template<typename T>
class Vec
{
public:
  vector<T> v;
  int size;

  Vec(vector<T> &v1)
  {
    v=v1;
    size=v1.size();
  }
};



#endif
