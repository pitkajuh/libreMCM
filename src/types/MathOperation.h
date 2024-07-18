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

  void SetOperator(const string &m)
  {
    if(m==ADD) math_operator=new Add;
    else if(m==SUBTRACT) math_operator=new Sub;
    else if(m==MULTIPLY) math_operator=new Mul;
    else if(m==DIVIDE) math_operator=new Div;
    else if(m==EXP) math_operator=new Exp;
  }

  void Set(Value *v, const string &m, Value *w)
  {
    v1=v;
    v2=w;
    SetOperator(m);
  }

  MathOperator *GetOp(){return math_operator;}
  Value *GetV1(){return v1;}
  Value *GetV2(){return v2;}
  double GetV1Value(){return v1->GetValue();}
  double GetV2Value(){return v2->GetValue();}
  void SetV1Value(const double &d){v1->SetValue(d);}
  void SetV2Value(const double &d){v2->SetValue(d);}
  void SetV1(Value *v){v1=v;}
  void SetV2(Value *v){v2=v;}
  void DV1(){delete v1;}
  void DV2(){delete v2;}
  void DM(){delete math_operator;}
  void CalculateResult(){result=GetOp()->Calculate1(GetV1Value(), GetV2Value());}
  virtual void Calculate()=0;
  virtual void Simplify()=0;
  virtual MathOperation *Clone()=0;
  virtual ~MathOperation()
  {
    cout<<"~MathOperation"<<'\n';
    delete v1;
    delete v2;
    delete math_operator;
  }
};

// template <class T>
// class Clone: public MathOperation
// {
// public:
//   virtual MathOperation *clone() const
//   {
//     return new T(static_cast<const T&>(*this));
//   }
// };

class VVMathOperation: public MathOperation
{
  // Variable-variable math operation

  void Simplify(){} // Cannot be simplified.
  void Calculate(){}
};

class CVMathOperation: public MathOperation
{
  // Constant-variable math operation

  void Simplify(){} // Cannot be simplified.
  void Calculate(){}
};

class CCMathOperation: public MathOperation
{
  // Constant-constant math operation

  void Simplify(){}
  void Calculate(){}
};

class NVMathOperation: public MathOperation
{
  // Numeric-variable math operation

  void Simplify(){} // Cannot be simplified.
  void Calculate(){}
};

class NCMathOperation: public MathOperation
{
  // Numeric-constant math operation

  void Simplify(){}
  void Calculate(){}
};

class CMMathOperation: public MathOperation
{
  // Constant-math math operation

  void Simplify(){}
  void Calculate(){}
};

class NMMathOperation: public MathOperation
{
  // Numeric-math math operation
private:
  MathOperation *previous;
public:
  void Simplify()
  {
    previous->Simplify();
    Value *v2=previous->GetV2();
    const double v2d=previous->result;
    SetV2(v2);
    SetV2Value(v2d);
    cout<<v2<<'\n';
    // previous->DV1();
    // previous->DM();
    // previous->DV2();

    // delete previous;
    // DV2();
  }
  NMMathOperation *Clone(){return new NMMathOperation(*this);}
  NMMathOperation(MathOperation *m, Value *w, const string &s)
  {
    previous=m;
    SetOperator(s);
    SetV1(w);
    Simplify();
  }

 virtual ~NMMathOperation()
  {
    cout<<"~NMMathOperation"<<'\n';
    previous->DV1();
    previous->DM();

    // previous->DV2();
    // delete previous;
    // DV1();
    // DV2();
    // DM();
  }

  void Calculate(){}
};

class MVMathOperation: public MathOperation
{
  // Math-variable math operation

  void Simplify(){}
  void Calculate(){}
};

class MMMathOperation: public MathOperation
{
  // Math-math math operation

  void Simplify(){}
  void Calculate(){}
};

class NNMathOperation: public MathOperation
{
public:
  // Numeric-numeric math operation

  void Calculate(){CalculateResult();}
  void Simplify()
  {
    Calculate();
    // DV1();
    // // DV2();
    // DM();
  }
  NNMathOperation *Clone(){return new NNMathOperation(*this);}
  virtual ~NNMathOperation()
  {
    cout<<"NNMathOperation"<<'\n';
    // DV1();
    // DV2();
    // DM();
  }
};

#endif
