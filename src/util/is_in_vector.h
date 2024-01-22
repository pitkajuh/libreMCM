/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef ISINVECTORF_H
#define ISINVECTORF_H

#include <vector>
#include <algorithm>

using std::vector;
using std::find;

template<typename T> bool is_in_vector(const vector<T> vec, const T f)
{
  // Checks if a string is in a string of vectors and return true/false.
  bool rt=false;

  if(find(vec.begin(), vec.end(), f)!=vec.end()){rt=true;}

  return rt;
}

#endif
