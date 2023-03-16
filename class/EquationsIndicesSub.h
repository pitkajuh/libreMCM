/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef EQUATIONSINDICESSUB_H
#define EQUATIONSINDICESSUB_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class EquationsIndicesSub
{
 public:
  vector<string> equation;
  vector<int> indices;
  vector<string> parameter_data;
  int in_indice;
};

#endif
