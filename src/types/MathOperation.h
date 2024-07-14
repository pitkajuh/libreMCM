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
#include "MathOperator.h"
#include "../global/mathconst.h"

class MathOperation;
class Value;
// class VVMathOperation: public MathOperation;
using MathOperations=std::vector<MathOperation*>;

class MathOperation
{
private:
  Value *v1;
  Value *v2;
  MathOperator *math_operator;
public:
  double result;

  void Set(Value *v, const string &m, Value *w)
  {
    v1=v;
    v2=w;

    if(m==ADD) math_operator=new Add;
    else if(m==SUBTRACT) math_operator=new Sub;
    else if(m==MULTIPLY) math_operator=new Mul;
    else if(m==DIVIDE) math_operator=new Div;
    else if(m==EXP) math_operator=new Exp;
    delete math_operator;
  }

  MathOperator *GetOp() {return math_operator;}
  Value *GetV1() {return v1;}
  Value *GetV2() {return v2;}
  virtual double Calculate()=0;
};

class Value
{
private:
  string name;
  double value;
public:
  void SetName(const string &s) {name=s;}
  void SetValue(const double &v) {value=v;}
  string GetName() {return name;}
  double GetValue() {return value;}
};

class Constant: public Value
{
 public:
  Constant(const string &s)
  {
    SetName(s);
  }
};

class Variable: public Value
{
public:
  Variable(const string &s)
  {
    SetName(s);
  }
};

class Numeric: public Value
{
public:
  Numeric(const double &v)
  {
    SetValue(v);
  }
};

class InitialValue: public Value
{
public:
};

class MathOperationValue: public Value
{
public:
  void Test(MathOperations &op, const unsigned int i)
  {
    MathOperation *m=op[i];
    Value *v1=m->GetV1();
    // cout<<<<'\n';
  }
};

class RadioNuclide: public InitialValue
{
private:
  double halflife;
public:
};

// class MathOperation
// {
// private:
//   Value *v1;
//   Value *v2;
//   MathOperator *math_operator;
// public:
//   double result;

//   void Set(Value *v, const string &m, Value *w)
//   {
//     v1=v;
//     v2=w;

//     if(m==ADD) math_operator=new Add;
//     else if(m==SUBTRACT) math_operator=new Sub;
//     else if(m==MULTIPLY) math_operator=new Mul;
//     else if(m==DIVIDE) math_operator=new Div;
//     else if(m==EXP) math_operator=new Exp;
//     delete math_operator;
//   }

//   MathOperator *GetOp() {return math_operator;}
//   Value *GetV1() {return v1;}
//   Value *GetV2() {return v2;}
//   virtual double Calculate()=0;
// };

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
  // Constant-constant math operation
  double Calculate()
  {
    return 0;
  }
};

class NVMathOperation: public MathOperation
{
  // Numeric-variable math operation
  double Calculate()
  {
    return 0;
  }
};

class NCMathOperation: public MathOperation
{
  // Numeric-constant math operation
  double Calculate()
  {
    return 0;
  }
};

class CMMathOperation: public MathOperation
{
  // Constant-math math operation
  double Calculate()
  {
    return 0;
  }
};

class NMMathOperation: public MathOperation
{
  // Numeric-math math operation
  double Calculate()
  {
    return 0;
  }
};

class MVMathOperation: public MathOperation
{
  // Math-variable math operation
  double Calculate()
  {
    return 0;
  }
};

class MMMathOperation: public MathOperation
{
  // Math-math math operation
  double Calculate()
  {
    return 0;
  }
};

class NumericMathOperation: public MathOperation
{
  // Numeric-numeric math operation
  double Calculate()
  {
    result=GetOp()->Calculate(GetV1()->GetValue(), GetV2()->GetValue());
    return result;
  }
};

#endif
