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
public:
  Value *v1;
  Value *v2;
  MathOperator *math_operator;
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
  MathOperation()=default;
  MathOperator *GetOp(){return math_operator;}
  Value *GetV1(){return v1;}
  Value *GetV2(){return v2;}
  double GetV1Value(){return v1->GetValue();}
  double GetV2Value(){return v2->GetValue();}
  void SetV1Value(const double &d){v1->SetValue(d);}
  void SetV2Value(const double &d){v2->SetValue(d);}
  void SetV1(Value *v){v1=v;}
  void SetV2(Value *v){v2=v;}
  void SetOp(MathOperator *m){math_operator=m;}
  void CalculateResult(){result=GetOp()->Calculate1(GetV1Value(), GetV2Value());}
  void DeleteOperator(){delete math_operator;}
  void DeleteV1(){delete v1;}
  void DeleteV2(){delete v2;}
  void Print(){cout<<"v1 "<<v1<<" "<<GetV1Value()<<" v2 "<<v2<<" "<<GetV2Value()<<" mathop "<<math_operator<<'\n';}
  // MathOperation& operator =(MathOperation &m)
  // {
  //   cout<<"Call MathOperation ="<<'\n';
  //   if(this!=&m)
  //     {
  // 	delete v1;
  // 	delete v2;
  // 	delete math_operator;
  // 	this->v1=m.v1;
  // 	this->v2=m.v2;
  // 	this->math_operator=m.math_operator;
  // 	m.v1=nullptr;
  // 	m.v2=nullptr;
  // 	m.math_operator=nullptr;
  //     }
  //   return *this;
  // }
  virtual void Init(MathOperation *m, Value *w, const string &s)=0;
  virtual void Type()=0;
  virtual void Calculate()=0;
  virtual void Simplify()=0;
  // virtual MathOperation *Clone()=0;
  // virtual MathOperation *New()=0;
  virtual ~MathOperation()
  {
    cout<<"Cleaning ~MathOperation()"<<'\n';
    // Print();
    cout<<"Cleaning v1 "<<v1<<'\n';
    delete v1;
    cout<<"Cleaning v2 "<<v2<<'\n';
    delete v2;
    cout<<"Cleaning math_operator "<<math_operator<<'\n';
    delete math_operator;
    cout<<"Cleaned ~MathOperation()"<<'\n';
    cout<<" "<<'\n';
  }
  // MathOperation(const MathOperation &m)
  // {
  //   cout<<"Default copy const MathOperation()"<<'\n';
  //   this->v1=m.v1;
  //   this->v2=m.v2;
  //   this->math_operator=m.math_operator;
  // }
  // MathOperation(MathOperation &&m)
  // {
  //   cout<<"Default move const MathOperation()"<<'\n';
  //   this->v1=m.v1;
  //   this->v2=m.v2;
  //   this->math_operator=m.math_operator;
  //   m.v1=nullptr;
  //   m.v2=nullptr;
  //   m.math_operator=nullptr;
  // }
};

class NMMathOperation: public MathOperation
{
  // Numeric-math math operation
public:
  // MathOperation *previous;

  // MathOperation *New()
  // {
  //   MathOperation *n=new NMMathOperation;
  //   return n;
  // }
  // NMMathOperation(const NMMathOperation &m):MathOperation(m)
  // {
  //   cout<<"NMMathOperation copy const"<<'\n';
  //   previous->SetV1(m.v1);
  //   previous->SetV2(m.v2);
  //   previous->SetOp(m.math_operator);
  // }
  // NMMathOperation(NMMathOperation &&m):MathOperation(std::move(m))
  // {
  //   cout<<"NMMathOperation move const"<<'\n';
  //   previous->SetV1(m.v1);
  //   previous->SetV2(m.v2);
  //   previous->SetOp(m.math_operator);

  //   // v2=m.v2;

  //   m.v1=nullptr;
  //   m.v2=nullptr;
  //   m.math_operator=nullptr;
  // }
  // NMMathOperation& operator =(NMMathOperation &m)
  // {
  //   cout<<"Call NMMathOperation ="<<'\n';
  //   if(this!=&m)
  //     {
  // 	delete previous;
  // 	previous->SetV1(m.v1);
  // 	previous->SetV2(m.v2);
  // 	previous->SetOp(m.math_operator);
  // 	m.v1=nullptr;
  // 	m.v2=nullptr;
  // 	m.math_operator=nullptr;
  //     }
  //   return *this;
  // }
  void Calculate()
  {
    CalculateResult();
    cout<<"result calculated "<<result<<'\n';
  }
  // void Simplify()
  // {
  //   previous->Simplify();
  //   cout<<"setting v2"<<'\n';

  //   // Value *v22=previous->v2;
  //   // cout<<"v22 "<<v22->GetValue()<<" "<<v22<<" "<<previous->v2<<'\n';
  //   // v22->Type();
  //   // // v22->SetValue(NAN);
  //   // SetV2(v22);
  //   // // SetV2(previous->v2);

  //   // // Value *v22=previous->v2;
  //   // // cout<<"v22 "<<v22->GetValue()<<" "<<v22<<" "<<previous->v2<<'\n';
  //   // // v22->Type();
  //   // // // v22->SetValue(NAN);
  //   // SetV2(previous->v2);
  //   // // SetV2(previous->v2);

  //   Value *v22=previous->GetV2()->Clone();
  //   cout<<"v22 "<<v22->GetValue()<<" "<<v22<<" "<<previous->v2<<'\n';
  //   v22->Type();
  //   SetV2(v22);

  //   v2->Type();
  //   cout<<"v2 set "<<GetV2Value()<<" "<<v2<<'\n';
  //   if(previous->result!=NAN)
  //     {
  // 	// cout<<"Setting v2 value "<<previous->result<<'\n';
  // 	SetV2Value(previous->result);
  // 	// cout<<"v2 value set "<<previous->result<<'\n';
  // 	Calculate();
  // 	// delete v22;
  //     }
  //   else
  //     {
  // 	cout<<"is nan"<<'\n';
  //     }
  //   // delete v22;
  //   cout<<" "<<'\n';
  // }
  void Simplify()
  {
    // previous->Simplify();
    // cout<<"setting v2"<<'\n';

    // Value *v22=previous->v2;
    // cout<<"v22 "<<v22->GetValue()<<" "<<v22<<" "<<previous->v2<<'\n';
    // v22->Type();
    // // v22->SetValue(NAN);
    // SetV2(v22);
    // // SetV2(previous->v2);

    // // Value *v22=previous->v2;
    // // cout<<"v22 "<<v22->GetValue()<<" "<<v22<<" "<<previous->v2<<'\n';
    // // v22->Type();
    // // // v22->SetValue(NAN);
    // SetV2(previous->v2);
    // // SetV2(previous->v2);

    // Value *v22=previous->GetV2()->Clone();
    // cout<<"v22 "<<v22->GetValue()<<" "<<v22<<" "<<previous->v2<<'\n';
    // v22->Type();
    // SetV2(v22);

    // v2->Type();
    // cout<<"v2 set "<<GetV2Value()<<" "<<v2<<'\n';
    // if(previous->result!=NAN)
    //   {
    // 	// cout<<"Setting v2 value "<<previous->result<<'\n';
    // 	SetV2Value(previous->result);
    // 	// cout<<"v2 value set "<<previous->result<<'\n';
    // 	Calculate();
    // 	// delete v22;
    //   }
    // else
    //   {
    // 	cout<<"is nan"<<'\n';
    //   }
    // // delete v22;
    // cout<<" "<<'\n';
  }
  // NMMathOperation(MathOperation *m, Value *w, const string &s):MathOperation()
  void Init(MathOperation *m, Value *w, const string &s)
  {
    // cout<<"setting previous=m"<<'\n';
    // previous=std::move(m);

    // previous=std::move(m);

    // previous->Set1(m);A
    // cout<<"previous: "<<m<<" "<<previous<<'\n';
    m->Print();
    SetV1(w);
    // SetV2(m->v2);
    v2=m->v2->New();
    v2->SetName(m->v2->GetName());
    v2->SetValue(m->v2->GetValue());
    SetOperator(s);

    cout<<"v2 set "<<GetV2Value()<<" "<<v2<<'\n';
    if(m->result!=NAN)
      {
	// cout<<"Setting v2 value "<<previous->result<<'\n';
	SetV2Value(m->result);
	// cout<<"v2 value set "<<previous->result<<'\n';
	Calculate();
	// delete v22;
      }
    else
      {
	cout<<"is nan"<<'\n';
      }
    // delete v22;
    cout<<" "<<'\n';

  }
  // NMMathOperation(MathOperation *m, Value *w, const string &s):MathOperation()
  // {
  //   // cout<<"setting previous=m"<<'\n';
  //   // previous=std::move(m);

  //   previous=std::move(m);

  //   // previous->Set1(m);A
  //   cout<<"previous: "<<m<<" "<<previous<<'\n';
  //   m->Print();
  //   SetV1(w);
  //   SetOperator(s);
  // }
  void Type(){cout<<"Type is NMMath"<<'\n';}
  // NMMathOperation *Clone()
  // {
  //   // cout<<"Cloning NMMathOperation"<<'\n';
  //   return new NMMathOperation(*this);
  // }

  // virtual ~NMMathOperation()
  // {
  //   cout<<"Attempting to clean ~NMMathOperation()"<<'\n';
  //   Print();
  //   cout<<"Clean "<<v22<<'\n';
  //   delete v22;
  //   // previous->DeleteV1();
  //   // previous->DeleteV2();
  //   // previous->DeleteOperator();
  //   // delete previous;
  //   // previous->DeleteOperator();
  //   cout<<"Not cleaned  ~NMMathOperation()"<<'\n';
  // }
};

class NNMathOperation: public MathOperation
{
public:
  // Numeric-numeric math operation

  // MathOperation *New()
  // {
  //   MathOperation *n=new NNMathOperation;
  //   return n;
  // }
  void Calculate(){CalculateResult();}
  void Simplify()
  {
    Calculate();
    cout<<"result "<<result<<'\n';
  }
  // NNMathOperation *Clone()
  // {
  //   // cout<<"Cloning NMMathOperation"<<'\n';
  //   return new NNMathOperation(*this);
  // }
  // NNMathOperation(Value *v, const string &m, Value *w)
  void Init(MathOperation *m, Value *w, const string &s)
  {
    // SetV1(v);
    // SetV2(w);
    // SetOperator(m);
  }
  void Type(){cout<<"Type is NNMath"<<'\n';}
  // NNMathOperation(const NNMathOperation &m):MathOperation(m)
  // {
  //   cout<<"NNMathOperation copy const"<<'\n';
  //   v1=m.v1;
  //   v2=m.v2;
  //   math_operator=m.math_operator;
  // }
  // NNMathOperation(NNMathOperation &&m):MathOperation(m)
  // {
  //   cout<<"NNMathOperation move const"<<'\n';
  //   v1=m.v1;
  //   v2=m.v2;
  //   math_operator=m.math_operator;
  //   m.v1=nullptr;
  //   m.v2=nullptr;
  //   m.math_operator=nullptr;
  // }
  // NNMathOperation& operator =(NNMathOperation &m)
  // {
  //   cout<<"Call NNMathOperation ="<<'\n';
  //   if(this!=&m)
  //     {
  // 	delete v1;
  // 	delete v2;
  // 	delete math_operator;
  // 	v1=m.v1;
  // 	v2=m.v2;
  // 	math_operator=m.math_operator;
  // 	m.v1=nullptr;
  // 	m.v2=nullptr;
  // 	m.math_operator=nullptr;
  //     }
  //   return *this;
  // }
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
