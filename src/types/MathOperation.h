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
#include <math.h>
#include "Value.h"
#include "MathOperator.h"
#include "../global/mathconst.h"

class MathOperation;
using MathOperations=std::vector<MathOperation*>;
#include <iostream>
using std::cout;
class MathOperation
{
private:
  Value *v1;
  Value *v2;
  MathOperator *math_operator;
public:
  double result;

  ~MathOperation()
  {
    delete v1;
    delete v2;
    delete math_operator;
  }

  void Set(Value *v, const string &m, Value *w)
  {
    v1=v;
    v2=w;

    if(m==ADD) math_operator=new Add;
    else if(m==SUBTRACT) math_operator=new Sub;
    else if(m==MULTIPLY) math_operator=new Mul;
    else if(m==DIVIDE) math_operator=new Div;
    else if(m==EXP) math_operator=new Exp;
    // delete math_operator;
  }

  MathOperator *GetOp() {return math_operator;}
  Value *GetV1() {return v1;}
  Value *GetV2() {return v2;}
  double GetV1Value() {return v1->GetValue();}
  double GetV2Value() {return v2->GetValue();}
  void CalculateResult()
  {
    // result=GetOp()->Calculate1(GetV1()->GetValue(), GetV2()->GetValue());
    double s1=GetV1Value();
    double s2=GetV2Value();
    // result=GetOp()->Calculate1(GetV1Value(), GetV2Value());
    result=GetOp()->Calculate1(s1, s2);
  }
  virtual void Calculate()=0;
};

class RadioNuclide: public InitialValue
{
private:
  double halflife;
public:
};

class VVMathOperation: public MathOperation
{
  // Variable-variable math operation
  void Calculate()
  {

  }
};

class CVMathOperation: public MathOperation
{
  // Constant-variable math operation
  void Calculate()
  {

  }
};

class CCMathOperation: public MathOperation
{
  // Constant-constant math operation
  void Calculate()
  {

  }
};

class NVMathOperation: public MathOperation
{
  // Numeric-variable math operation
  void Calculate()
  {

  }
};

class NCMathOperation: public MathOperation
{
  // Numeric-constant math operation
  void Calculate()
  {

  }
};

class CMMathOperation: public MathOperation
{
  // Constant-math math operation
  void Calculate()
  {

  }
};

class NMMathOperation: public MathOperation
{
  // Numeric-math math operation
  void Calculate()
  {

  }
};

class MVMathOperation: public MathOperation
{
  // Math-variable math operation
  void Calculate()
  {

  }
};

class MMMathOperation: public MathOperation
{
  // Math-math math operation
  void Calculate()
  {

  }
};

class NumericMathOperation: public MathOperation
{
  // Numeric-numeric math operation
  void Calculate()
  {
    // result=GetOp()->Calculate1(GetV1()->GetValue(), GetV2()->GetValue());
    // return result;
    // return CalculateResult();
    CalculateResult();
  }
};

#endif
