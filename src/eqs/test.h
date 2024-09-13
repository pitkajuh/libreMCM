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

vector<string> test(vector<string> equation, unsigned &k, const Data &data, Equation *&e, Equation *&next);
vector<string> Remove(vector<string> equation, const unsigned open, const unsigned close);

#endif
