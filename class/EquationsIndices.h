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
#include "../class/SplittedString.h"

class EquationsIndices
{
 public:
  vector<string> equation;
  vector<int> indices;
  vector<SplittedString> parameter_data;
  // int in_indice;
};

#endif
