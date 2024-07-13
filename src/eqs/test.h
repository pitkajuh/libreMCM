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
#include <algorithm>

vector<string> test(vector<string> equation,  unsigned int &k, MathOperations &ooo, const Data &data);
vector<string> Remove(vector<string> equation,  const int &open,  const int &close);

#endif
