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
  void CalculateResult(){result=GetOp()->Calculate1(GetV1Value(), GetV2Value());}
  void Print(){cout<<"v1 "<<v1<<" "<<GetV1Value()<<" v2 "<<v2<<" "<<GetV2Value()<<" mathop "<<math_operator<<'\n';}
  virtual void Init(MathOperation *m, Value *w, const string &s)=0;
  virtual void Type()=0;
  virtual void Calculate()=0;
  virtual ~MathOperation()
  {
    // cout<<"Cleaning ~MathOperation()"<<'\n';
    // cout<<"Cleaning v1 "<<v1<<'\n';
    delete v1;
    // cout<<"Cleaning v2 "<<v2<<'\n';
    delete v2;
    // cout<<"Cleaning math_operator "<<math_operator<<'\n';
    delete math_operator;
    // cout<<"Cleaned ~MathOperation()"<<'\n';
    cout<<" "<<'\n';
  }
};

class NMMathOperation: public MathOperation
{
  // Numeric-math math operation
public:
  void Type(){cout<<"Type is NMMath"<<'\n';}
  void Calculate()
  {
    CalculateResult();
    cout<<"result calculated "<<result<<'\n';
  }

  void Init(MathOperation *m, Value *w, const string &s)
  {
    m->Print();
    SetV1(w);
    SetV2(m->GetV2()->New());
    GetV2()->SetName(m->GetV2()->GetName());
    GetV2()->SetValue(m->GetV2()->GetValue());
    SetOperator(s);

    cout<<"v2 set "<<GetV2Value()<<" "<<GetV2()<<'\n';
    if(m->result!=NAN)
      {
	// cout<<"Setting v2 value "<<previous->result<<'\n';
	SetV2Value(m->result);
	// cout<<"v2 value set "<<previous->result<<'\n';
	Calculate();
      }
    else
      {
	cout<<"is nan"<<'\n';
      }
    cout<<" "<<'\n';
  }
};

class NNMathOperation: public MathOperation
{
  // Numeric-numeric math operation
public:
  void Calculate(){CalculateResult();}
  void Init(MathOperation *m, Value *w, const string &s){}
  void Type(){cout<<"Type is NNMath"<<'\n';}
};

// class VVMathOperation: public MathOperation
// {
//   // Variable-variable math operation

//   void Calculate(){}
// };

class CVMathOperation: public MathOperation
{
  // Constant-variable math operation
public:
  void Calculate(){}
  void Init(MathOperation *m, Value *w, const string &s){}
  void Type(){cout<<"Type is CVMath"<<'\n';}
};

class CCMathOperation: public MathOperation
{
  // Constant-constant math operation
public:
  void Calculate(){}
  void Init(MathOperation *m, Value *w, const string &s){}
  void Type(){cout<<"Type is CCMath"<<'\n';}
};

class NVMathOperation: public MathOperation
{
  // Numeric-variable math operation
public:
  void Calculate(){}
  void Init(MathOperation *m, Value *w, const string &s){}
  void Type(){cout<<"Type is NVMath"<<'\n';}
};

// class NCMathOperation: public MathOperation
// {
//   // Numeric-constant math operation

//   void Calculate(){}
// };

// class CMMathOperation: public MathOperation
// {
//   // Constant-math math operation

//   void Calculate(){}
// };

class MVMathOperation: public MathOperation
{
  // Math-variable math operation
public:
  void Calculate(){}
  void Init(MathOperation *m, Value *w, const string &s){}
  void Type(){cout<<"Type is MVMath"<<'\n';}
};

class MMMathOperation: public MathOperation
{
   // Math-math math operation

  void Calculate()
  {
    CalculateResult();
    cout<<"result calculated "<<result<<'\n';
  }
  void Init(MathOperation *m, Value *w, const string &s){}
  void Type(){cout<<"Type is MMMath"<<'\n';}
};

#endif
