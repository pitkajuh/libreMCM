/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "ToVector.h"
#include "../types/MathOperation.h"
#include <unordered_map>
#include <algorithm>
#include <iostream>

using std::unordered_map;
using std::to_string;
using std::cout;
using MathOperations=unordered_map<string, OpTmp>;

vector<string> test(vector<string> equation,  unsigned int &k, MathOperations &ooo);
vector<string> Remove(vector<string> equation,  const int &open,  const int &close);
