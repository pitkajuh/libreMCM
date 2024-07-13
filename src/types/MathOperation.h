/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef MATHOPERATION_H
#define MATHOPERATION_H

#include <vector>
#include "Value.h"
#include "MathOperator.h"
#include "../global/mathconst.h"

using std::vector;
class MathOperation;
using MathOperations=vector<MathOperation>;

class MathOperation
{
public:
  Value* v1;
  Value* v2;
  MathOperator* math_operator;
  double result;

  void SetMathOp(const string &m)
  {
    if(m==ADD) math_operator=new Add;
    else if(m==SUBTRACT) math_operator=new Sub;
    else if(m==MULTIPLY) math_operator=new Mul;
    else if(m==DIVIDE) math_operator=new Div;
    else if(m==EXP) math_operator=new Exp;
    delete math_operator;
  }

  void SetValues(Value* v, Value* w)
  {
    v1=v;
    v2=w;
  }

  // void Calculate() {result=math_operator->Calculate(v1->value, v2->value);}
  // virtual double Calculate()=0;
};

class NumericMathOperation: public MathOperation
{
  // double Calculate()
  // {
  //   return 0;
  // }
};

#endif
