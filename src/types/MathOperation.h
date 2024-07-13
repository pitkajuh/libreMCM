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

#include "Value.h"
#include "MathOperator.h"
#include "../global/mathconst.h"

struct OpTmp
{
  string value1;
  string value2;
  MathOperator* math_operator;

  void SetMathOp(const string &m)
  {
    if(m==ADD) math_operator=new Add;
    else if(m==SUBTRACT) math_operator=new Sub;
    else if(m==MULTIPLY) math_operator=new Mul;
    else if(m==DIVIDE) math_operator=new Div;
    else if(m==EXP) math_operator=new Exp;
    delete math_operator;
  }

  void Set(const string &v1, const string &op, const string &v2)
  {
    value1=v1;
    value2=v2;
    SetMathOp(op);
  }
};

class MathOperation
{
public:
  Value* v1;
  Value* v2;
  MathOperator* math_op;
  double result;

  void SetMathOp(MathOperator* o)
  {
    math_op=o;
  }

  void Calculate() {result=math_op->Calculate(v1->value, v2->value);}
};

#endif
