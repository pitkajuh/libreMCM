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
#include "../inc/namespace.h"
#include "../types/MathOperation.h"
#include <algorithm>

using namespace libremcm;
using MathOperations=map<string, OpTmp>;

vector<string> test(vector<string> equation,  unsigned int &k, MathOperations &ooo);
vector<string> Remove(vector<string> equation,  const int &open,  const int &close);

#endif
