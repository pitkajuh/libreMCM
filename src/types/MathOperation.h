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
// #include "../global/matrix.h"
#include "../global/mathconst.h"
// #include "../util/is_in_vector.h"

class MathOperator
{
public:
  virtual double Calculate(const double v1, const double v2)=0;
  ~MathOperator(){}
};

class Add:public MathOperator
{
public:
  double Calculate(const double v1, const double v2) return v1+v2;
};

class Sub:public MathOperator
{
public:
  double Calculate(const double v1, const double v2) return v1-v2;
};

class Mul:public MathOperator
{
public:
  double Calculate(const double v1, const double v2) return v1*v2;
};

class Div:public MathOperator
{
public:
  double Calculate(const double v1, const double v2) return v1/v2;
};

class Exp:public MathOperator
{
public:
  double Calculate(const double v1, const double v2) return v1^v2;
};

class MathOperation
{
public:
  string id;
  Value* v1;
  Value* v2;
  MathOperator* math_op;
  double result;

  // void SetValue1(const string x)
  // {
  //   bool variable=is_in_vector(Matrix.diagonal2, x);
  //   if(variable) v1=new Variable;
  //   else v1=new Constant(x);
  // }

  // void SetValue2(const string x)
  // {
  //   bool variable=is_in_vector(Matrix.diagonal2, x);
  //   if(variable) v2=new Variable;
  //   else v2=new Constant(x);
  // }

  void SetMathOp(const string m)
  {
    if(m==ADD) math_op=new Add;
    else if(m==SUBTRACT) math_op=new Sub;
    else if(m==MULTIPLY) math_op=new Mul;
    else if(m==DIVIDE) math_op=new Div;
    else if(m==EXP) math_op=new Exp;
  }

  ~MathOperation()
  {
    delete math_op;
    delete v1;
    delete v2;
  }

};

#endif
