/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef NAMESPACE_H
#define NAMESPACE_H

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

namespace libremcm
{
  template<typename T, typename U> using map= unordered_map<T, U>;
  using smap=map<string, string>;
}

#endif
