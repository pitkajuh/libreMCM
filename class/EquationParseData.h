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

#include <vector>
#include "../class/SplittedString.h"

using std::vector;

class EquationParseData
{
 public:
  vector<string> equation;
  vector<int> indices;
  vector<SplittedString> compartments;
};

#endif
