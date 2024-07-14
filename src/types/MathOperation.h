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

class MathOperation;
using MathOperations=std::vector<MathOperation*>;

class MathOperation
{
private:
  Value *v1;
  Value *v2;
  MathOperator *math_operator;
public:
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

  void SetValues(Value *v, Value *w)
  {
    v1=v;
    v2=w;
  }

  MathOperator *GetOp() {return math_operator;}
  Value *GetV1() {return v1;}
  Value *GetV2() {return v2;}


  virtual double Calculate()=0;
};

class VVMathOperation: public MathOperation
{
  // Variable-variable math operation
  double Calculate()
  {
    return 0;
  }
};

class CVMathOperation: public MathOperation
{
  // Constant-variable math operation
  double Calculate()
  {
    return 0;
  }
};

class CCMathOperation: public MathOperation
{
  // Constant-variable math operation
  double Calculate()
  {
    return 0;
  }
};

class NVMathOperation: public MathOperation
{
  // Constant-variable math operation
  double Calculate()
  {
    return 0;
  }
};

class NCMathOperation: public MathOperation
{
  // Constant-variable math operation
  double Calculate()
  {
    return 0;
  }
};

class CMMathOperation: public MathOperation
{
  // Constant-variable math operation
  double Calculate()
  {
    return 0;
  }
};

class NMMathOperation: public MathOperation
{
  // Constant-variable math operation
  double Calculate()
  {
    return 0;
  }
};

class MVMathOperation: public MathOperation
{
  // Constant-variable math operation
  double Calculate()
  {
    return 0;
  }
};

class MMMathOperation: public MathOperation
{
  // Constant-variable math operation
  double Calculate()
  {
    return 0;
  }
};

class NumericMathOperation: public MathOperation
{
  // For purely numeric values
  double Calculate()
  {
    result=GetOp()->Calculate(GetV1()->GetValue(), GetV2()->GetValue());
    return result;
  }
};

#endif
