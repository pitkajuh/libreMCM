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

// void

Value* ValueCheck(const string &s, const vector<string> diagonal, const unordered_map<string, string> &constants_map)
{
  const bool is_variable=IsIn(s, diagonal);
  const bool is_constant=IsIn(s, constants_map);
  const bool is_numerical=IsNumerical(s);

  if(is_variable)
    {
      Value *v=new Variable(s);
      return v;
    }
  else if(is_constant)
    {
      Value *v=new Constant(s);
      return v;
    }
  // else if(is_numerical)
  else
    {
      Value *v=new Value(s);
      return v;
    }
  // else if(is_constant)
  //   {
  //     v=new Constant(s);
  //     // v->name=s;
  //   }
  // v->name=s;
  // const bool is_numerical=IsNumerical(s);
  // delete v;
  // return v;
}

void GetValue(const vector<OpTmp> &v, const vector<string> diagonal, const unordered_map<string, string> &constants_map)
{
  Value *v1;
  // MathOperation op;

  for(const auto &i: v)
    {
      // v1=i.value1;
      // v2=i.value2;
      v1=ValueCheck(i.value1, diagonal, constants_map);
      // op.v1=v1;
      delete v1;
    }
  // delete v1;
  // return v1;
}

void CreateEquationTemplates(const unordered_map<string, MathOperations> &equations_map, const Csv &csv, const unordered_map<string, string> &constants_map)
{
  const vector<string> diagonal=csv.diagonal;
  // Value *v1=new Value;

  for(const auto &[key, value]: equations_map)
    {
      // v1=GetValue(value, diagonal, constants_map);
      GetValue(value, diagonal, constants_map);
    }
  // delete v1;
  // cout<<"aoe "<<IsIn("void", diagonal)<<" "<<IsIn("void", constants_map)<<'\n';
  cout<<"aoe "<<IsIn("a", constants_map)<<'\n';
}
