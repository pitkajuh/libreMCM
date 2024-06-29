/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../util/IsIn.h"
#include "../types/MathOperation.h"
#include "../types/Csv.h"
#include <iostream>
#include <stdexcept>

using std::cout;
using MathOperations=unordered_map<string, OpTmp>;

Value* ValueCheck(const string &s, const vector<string> &diagonal, unordered_map<string, string> &constants_map, const MathOperations &v)
{
  const bool is_variable=IsIn(s, diagonal);
  const bool is_constant=IsIn(s, constants_map);
  const bool is_math=IsIn(s, v);
  const bool is_numerical=IsNumerical(s);

  if(is_variable)
    {
      Value *v=new Variable(s);
      return v;
    }
  else if(is_constant)
    {
      Value *v=new Constant(s, std::stod(constants_map[s]));
      return v;
    }
  else if(is_numerical)
    {
      Value *v=new Value(s, std::stod(s));
      return v;
    }
  else if(is_math)
    {
      Value *v=new Value(s, 0);
      return v;
    }
  else throw std::invalid_argument("Value "+s+" is not a constant, variable or numerical value.");
}

MathOperation *GetValue(const MathOperations &v, const vector<string> &diagonal, unordered_map<string, string> &constants_map)
{
  Value *v1;
  Value *v2;
  MathOperation *op=new MathOperation;

  for(const auto &[key, value]: v)
    {
      v1=ValueCheck(value.value1, diagonal, constants_map, v);
      v2=ValueCheck(value.value2, diagonal, constants_map, v);
      // cout<<v1->value<<value.math_operator<<v2->value<<'\n';
      op->v1=v1;
      op->SetMathOp(value.math_operator);
      op->v2=v2;
      delete v1;
      delete v2;
    }
  return op;
}

void CreateEquationTemplates(const unordered_map<string, MathOperations> &equations_map, const Csv &csv, unordered_map<string, string> &constants_map)
{
  const vector<string> diagonal=csv.diagonal;
  MathOperation *op;

  for(const auto &[key, value]: equations_map)
    {
      op=GetValue(value, diagonal, constants_map);
      delete op;
    }
}
