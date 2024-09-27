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

class MathOperationBase
{
public:
  double result=NAN;

  virtual ~MathOperationBase(){}
};

class MathOperation: public MathOperationBase
{
protected:
   MathOperator *math_operator;
private:
  Value *v1;
  Value *v2;
public:
  void SetOperator(const string &s)
  {
    if(s==ADD) math_operator=new Add;
    else if(s==SUBTRACT) math_operator=new Sub;
    else if(s==MULTIPLY) math_operator=new Mul;
    else if(s==DIVIDE) math_operator=new Div;
    else if(s==EXP) math_operator=new Exp;
  }
  double GetV1Value(){return v1->GetValue();} const
  double GetV2Value(){return v2->GetValue();} const
  string GetV1Name(){return v1->GetName();} const
  string GetV2Name(){return v2->GetName();} const
  void SetV1(Value *v){v1=v;}
  void SetV2(Value *v){v2=v;}
  void Calculate(){result=math_operator->Calculate(GetV1Value(), GetV2Value());}
  ~MathOperation()
  {
    delete v1;
    delete v2;
    delete math_operator;
  }
};

class NumericNumeric: public MathOperation
{
  // Numeric-numeric math operation
public:
};

class VariableVariable: public MathOperation
{
  // Variable-variable math operation
public:
};

class ConstantVariable: public MathOperation
{
  // Constant-variable math operation
public:
};

class ConstantConstant: public MathOperation
{
  // Constant-constant math operation
public:
};

class NumericVariable: public MathOperation
{
  // Numeric-variable math operation
public:
};

class NumericConstant: public MathOperation
{
  // Numeric-constant math operation
public:
};

#endif
