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
void Print()
  {
    // cout<<v1<<" "<<v2<<" "<<math_operator<<'\n';
  }
  MathOperator *GetOp(){return math_operator;}
  Value *GetV1(){return v1;}
  Value *GetV2(){return v2;}
  double GetV1Value(){return v1->GetValue();}
  double GetV2Value(){return v2->GetValue();}
  void SetV1Value(const double &d){v1->SetValue(d);}
  void SetV2Value(const double &d)
  {
    cout<<"d="<<d<<'\n';
    v2->SetValue(d);
  }
  void SetV1(Value *v){v1=v;}
  void SetV2(Value *v){v2=v;}
  void CalculateResult(){result=GetOp()->Calculate1(GetV1Value(), GetV2Value());}
  virtual void Type()=0;
  virtual void Calculate()=0;
  virtual void Simplify()=0;
  virtual MathOperation *Clone()=0;
  virtual ~MathOperation()
  {
    cout<<"Cleaning ~MathOperation()"<<'\n';
    Print();
    delete v1;
    delete v2;
    delete math_operator;
    cout<<"Cleaned  ~MathOperation()"<<'\n';
    cout<<" "<<'\n';
  }
  // virtual ~MathOperation()=0;
  // {
  //   cout<<"Cleaning ~MathOperation()"<<'\n';
  //   Print();
  //   delete v1;
  //   delete v2;
  //   delete math_operator;
  //   cout<<"Cleaned  ~MathOperation()"<<'\n';
  // }
};

// class VVMathOperation: public MathOperation
// {
//   // Variable-variable math operation

//   void Simplify(){} // Cannot be simplified.
//   void Calculate(){}
// };

// class CVMathOperation: public MathOperation
// {
//   // Constant-variable math operation

//   void Simplify(){} // Cannot be simplified.
//   void Calculate(){}
// };

// class CCMathOperation: public MathOperation
// {
//   // Constant-constant math operation

//   void Simplify(){}
//   void Calculate(){}
// };

// class NVMathOperation: public MathOperation
// {
//   // Numeric-variable math operation

//   void Simplify(){} // Cannot be simplified.
//   void Calculate(){}
// };

// class NCMathOperation: public MathOperation
// {
//   // Numeric-constant math operation

//   void Simplify(){}
//   void Calculate(){}
// };

// class CMMathOperation: public MathOperation
// {
//   // Constant-math math operation

//   void Simplify(){}
//   void Calculate(){}
// };

class NMMathOperation: public MathOperation
{
  // Numeric-math math operation
private:
  MathOperation *previous;
public:
  // void Simplify()
  // {
  //   previous->Simplify();
  //   Value *v2=previous->GetV2()->Clone();
  //   SetV2(v2);
  //   SetV2Value(previous->result);
  // }

  void Simplify()
  {
    // previous->Simplify();
    cout<<"setting v2"<<'\n';
    Value *v2=previous->GetV2()->Clone();
    // // cout<<"v2->GetValue() "<<v2->GetValue()<<'\n';
    SetV2(v2);
    SetV2Value(previous->result);
    // cout<<"v2->GetValue() "<<v2->GetValue()<<'\n';
    cout<<"v2->result "<<previous->result<<'\n';
  }

  // NMMathOperation(MathOperation *m, Value *w, const string &s)
  // {
  //   // previous=m;
  //   previous=m->Clone();
  //   previous->SetV1(m->GetV1());
  //   cout<<"previous->GetV1Value() "<<previous->GetV1Value()<<'\n';
  //   previous->SetV2(m->GetV2());
  //   // cout<<"previous->GetV2Value() "<<previous->GetV2Value()<<'\n';
  //   previous->SetOperator(s);
  //   SetOperator(s);
  //   SetV1(w);
  //   Simplify();
  // }

  // NMMathOperation(MathOperation *m, Value *w, const string &s)
  // {
  //   previous=m;
  //   // previous=m->Clone();
  //   SetOperator(s);
  //   SetV1(w);
  //   Simplify();
  // }


  NMMathOperation(MathOperation *m, Value *w, const string &s)
  {
    previous=m;
    SetOperator(s);
    SetV1(w);
  }
  void Type()
  {
    cout<<"NMMath"<<'\n';
  }

  // NMMathOperation(MathOperation *m, Value *w, const string &s)
  // {
  //   // previous=m;
  //   previous=m->Clone();
  //   SetOperator(s);
  //   SetV1(w);
  //   Simplify();
  // }
  NMMathOperation *Clone(){return new NMMathOperation(*this);}
  void Calculate(){}
  // virtual ~NMMathOperation()
  // {
  //   cout<<"Cleaning ~NMMathOperation()"<<'\n';
  //   Print();
  //   delete previous;
  //   cout<<"Cleaned  ~NMMathOperation()"<<'\n';
  // }
};

// class MVMathOperation: public MathOperation
// {
//   // Math-variable math operation

//   void Simplify(){}
//   void Calculate(){}
// };

// class MMMathOperation: public MathOperation
// {
//   // Math-math math operation

//   void Simplify(){}
//   void Calculate(){}
// };

class NNMathOperation: public MathOperation
{
public:
  // Numeric-numeric math operation

  void Calculate(){CalculateResult();}
  void Simplify()
  {
    Calculate();
    cout<<"result "<<result<<'\n';
  }
  NNMathOperation *Clone(){return new NNMathOperation(*this);}
  NNMathOperation(Value *v, const string &m, Value *w)
  {
    SetV1(v);
    SetV2(w);
    SetOperator(m);
  }
  void Type()
  {
    cout<<"NNMath"<<'\n';
  }
  // ~NNMathOperation()
  // {
  //   delete v1;
  //   delete v2;
  //   delete math_operator;
  // }
};

#endif
