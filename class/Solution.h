/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef SOLUTION_H
#define SOLUTION_H

#include "EquationsIndices.h"

class Solution
{
 public:
  string compartment;
  EquationsIndices final_eq1;
  vector<int> indices_for_ks;
  vector<string> multiple_last_values;
  vector<string> parameter_data_for_indices;
};

#endif
