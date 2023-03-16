/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef DATA_H
#define DATA_H

#include "Equations.h"
#include "VecVecInt.h"
#include "SplittedStrings.h"

class Data
{
 public:
  Equations equations_sorted;
  VecVecInt calc_order_sorted;
  VecVecInt indice_values_sorted;
  SplittedStrings param_data_sorted;
};

#endif
