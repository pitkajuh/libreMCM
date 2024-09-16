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

vector<string> test(vector<string> equation, uint16_t &id, const Data &data, Equation *&head, Equation *&next);
vector<string> Remove(vector<string> equation, const uint16_t open, const uint16_t close);

#endif
