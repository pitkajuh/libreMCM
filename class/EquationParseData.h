/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef EQUATIONPARSEDATA_H
#define EQUATIONPARSEDATA_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class EquationParseData
{
 public:
  vector<string> equation;
  vector<int> indices;
  bool add_equation;
  vector<string> compartments;
};

#endif
