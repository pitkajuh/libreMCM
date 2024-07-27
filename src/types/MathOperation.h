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
  double result=NAN;

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
    cout<<"v1 "<<v1<<" v2 "<<v2<<" mathop "<<math_operator<<'\n';
  }
  MathOperator *GetOp(){return math_operator;}
  Value *GetV1(){return v1;}
  Value *GetV2(){return v2;}
  double GetV1Value(){return v1->GetValue();}
  double GetV2Value(){return v2->GetValue();}
  void SetV1Value(const double &d){v1->SetValue(d);}
  void SetV2Value(const double &d)
  {
    // cout<<"d="<<d<<'\n';
    v2->SetValue(d);
  }
  void SetV1(Value *v){v1=v;}
  void SetV2(Value *v){v2=v;}
  void CalculateResult(){result=GetOp()->Calculate1(GetV1Value(), GetV2Value());}
  void DeleteOperator(){delete math_operator;}
  void DeleteV1(){delete v1;}
  void DeleteV2(){delete v2;}
  virtual void Type()=0;
  virtual void Calculate()=0;
  virtual void Simplify()=0;
  virtual MathOperation *Clone()=0;
  // virtual ~MathOperation();
  virtual ~MathOperation()
  {
    cout<<"Cleaning ~MathOperation()"<<'\n';
    Print();
    delete v1;
    delete v2;
    delete math_operator;
    cout<<"Cleaned ~MathOperation()"<<'\n';
    cout<<" "<<'\n';
  }

  // MathOperation(MathOperation &m)
  // {
  //   v1=m.v1;
  //   v2=m.v2;
  //   math_operator=m.math_operator;
  // }
  // MathOperation& operator =(const MathOperation &m)
  // {
  //   v1=m.v1;
  //   v2=m.v2;
  //   return *this;
  // }
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

class NMMathOperation: public MathOperation
{
  // Numeric-math math operation
private:
  MathOperation *previous;
public:
  void SetPrevious(MathOperation *m)
  {
    previous=m;
    // previous=m->Clone();
    // previous->SetV2(m->GetV2());
    // previous->SetV1(m->GetV1());
    // // delete m;
    // m=nullptr;
    // previous->DeleteOperator();
    cout<<"previous: "<<m<<" "<<previous<<'\n';
    previous->Print();
    // delete m;
    // m->Print();
    // previous->Type();
    // cout<<"Previous Set"<<'\n';
  }
  void Calculate()
  {
    CalculateResult();
    cout<<"result calculated "<<result<<'\n';
  }
  void Simplify()
  {
    previous->Simplify();
    // cout<<"setting v2"<<'\n';
    Value *v2=previous->GetV2()->Clone();
    // cout<<"v2 set"<<'\n';
    SetV2(v2);

    if(previous->result!=NAN)
      {
	// cout<<"Setting v2 value "<<previous->result<<'\n';
	SetV2Value(previous->result);
	// cout<<"v2 value set "<<previous->result<<'\n';
	Calculate();
	// delete previous;
      }
    else
      {
	cout<<"is nan"<<'\n';
      }
    // Simplify();
    // delete previous;
    // DeleteV2();
  }
  NMMathOperation(MathOperation *m, Value *w, const string &s)
  {
    // cout<<"setting previous=m"<<'\n';
    SetPrevious(m);
    previous->Type();
    SetOperator(s);
    SetV1(w);
  }
  void Type()
  {
    cout<<"Type is NMMath"<<'\n';
  }
  NMMathOperation *Clone()
  {
    // cout<<"Cloning NMMathOperation"<<'\n';
    return new NMMathOperation(*this);
  }

  virtual ~NMMathOperation()
  {
    cout<<"Attempting to clean ~NMMathOperation()"<<'\n';
    Print();
    // previous->DeleteV1();
    // previous->DeleteV2();
    // previous->DeleteOperator();
    // delete previous;
    // previous->DeleteOperator();
    cout<<"Not cleaned  ~NMMathOperation()"<<'\n';
  }
};

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
  NNMathOperation *Clone()
  {
    // cout<<"Cloning NMMathOperation"<<'\n';
    return new NNMathOperation(*this);
  }
  NNMathOperation(Value *v, const string &m, Value *w)
  {
    SetV1(v);
    SetV2(w);
    SetOperator(m);
  }
  void Type(){cout<<"Type is NNMath"<<'\n';}
  // virtual ~NNMathOperation()
  // {
  //   cout<<"Attemp to clean ~NNMathOperation()"<<'\n';
  //   Print();
  //   // DeleteV1();
  //   // DeleteV2();
  //   // DeleteOperator();
  //   // delete v1;
  //   // delete v2;
  //   // delete math_operator;
  //   cout<<"Not cleaned  ~NNMathOperation()"<<'\n';
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

#endif
