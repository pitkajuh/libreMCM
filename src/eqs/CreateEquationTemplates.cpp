/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../types/MathOperation.h"
#include "../types/Data.h"
#include <iostream>

using std::cout;

void GetValue(MathOperations v, const Data &data)
{
  int j=0;
  for(const auto &i: v)
    {
      i->CalculateResult();
      cout<<j<<" "<<i->GetV1Value()<<" "<<i->GetV2Value()<<" "<<i->result<<'\n';
      delete i;
      j++;
    }
}

void CreateEquationTemplates(const Map<string, MathOperations> &equations_map, const Data &data)
{
  // MathOperation *op;

  for(const auto &[key, value]: equations_map)
    {
      cout<<key<<'\n';
      GetValue(value, data);
    }
}
