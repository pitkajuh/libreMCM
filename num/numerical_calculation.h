/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef NUMERICALCALCULATION_H
#define NUMERICALCALCULATION_H

#include "../util/combine_vectors.h"

void calculate();
void runge_kutta();
extern string comp_name_glob;
extern double h;

#endif
