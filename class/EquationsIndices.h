/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef EQUATIONSINDICES_H
#define EQUATIONSINDICES_H

#include "EquationsIndicesSub.h"

class EquationsIndices
{
 public:
  vector<string> equation;
  vector<int> indices;
  vector<string> parameter_data;
  int in_indice;
};

#endif
