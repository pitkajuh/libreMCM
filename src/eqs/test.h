/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef TEST_H
#define TEST_H

#include "ToVector.h"
#include "../types/MathOperation.h"
#include "../types/Data.h"
#include "../types/Equation.h"

vector<string> test(vector<string> equation, unsigned int &k, const Data &data, Equation *e, Equation *next, EquationStruct &eq);
vector<string> Remove(vector<string> equation, const int &open, const int &close);

#endif
