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
  string math_operator;

  void Set(const string &v1, const string &op, const string &v2)
  {
    value1=v1;
    value2=v2;
    math_operator=op;
  }
};

class MathOperation
{
public:
  Value* v1;
  Value* v2;
  MathOperator* math_op;
  double result;

  void SetMathOp(const string &m)
  {
    if(m==ADD) math_op=new Add;
    else if(m==SUBTRACT) math_op=new Sub;
    else if(m==MULTIPLY) math_op=new Mul;
    else if(m==DIVIDE) math_op=new Div;
    else if(m==EXP) math_op=new Exp;
    delete math_op;
  }

  void LinkMathOp()
  {

  }
};

#endif
