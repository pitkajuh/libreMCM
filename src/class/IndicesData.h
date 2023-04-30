/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef INDICESDATA_H
#define INDICESDATA_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class IndicesData
{
 public:
  vector<string> names;
  vector<int> indices;
};

#endif
