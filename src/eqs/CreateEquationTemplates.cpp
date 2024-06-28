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
#include "test.h"
#include "../util/IsIn.h"
#include "../global/mathconst.h"
#include "../types/MathOperation.h"
#include "../types/EquationTemplate.h"
#include "../types/Csv.h"
#include <iostream>

using std::cout;
using MathOperations=vector<OpTmp>;

void CreateEquationTemplates(const unordered_map<string, MathOperations> &equations_map, const Csv &csv, const unordered_map<string, string> &constants_map)
{
  const vector<string> diagonal=csv.diagonal;

  cout<<"aoe "<<IsIn("void", diagonal)<<'\n';

}
