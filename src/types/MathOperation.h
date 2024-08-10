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

#include <iostream>
using std::cout;

class MathOperation
{
private:
  Value *v1;
  Value *v2;
  MathOperator *math_operator;
public:
  int id;
  double result=NAN;

  MathOperation *next=nullptr;

  void SetOperator(const string &s)
  {
    if(s==ADD) math_operator=new Add;
    else if(s==SUBTRACT) math_operator=new Sub;
    else if(s==MULTIPLY) math_operator=new Mul;
    else if(s==DIVIDE) math_operator=new Div;
    else if(s==EXP) math_operator=new Exp;
  }
  void Set(Value *v, const string &s, Value *w)
  {
    v1=v;
    v2=w;
    SetOperator(s);
  }
  MathOperation()=default;
  MathOperator *GetOp(){return math_operator;} const
  void SetOp(MathOperator *m){math_operator=m;}
  Value *GetV1(){return v1;}
  Value *GetV2(){return v2;} const
  double GetV1Value(){return v1->GetValue();} const
  double GetV2Value(){return v2->GetValue();} const
  string GetV1Name(){return v1->GetName();} const
  string GetV2Name(){return v2->GetName();} const
  void SetV1Value(const double &d){v1->SetValue(d);} const
  void SetV2Value(const double &d){v2->SetValue(d);} const
  void SetV1(Value *v){v1=v;}
  void SetV2(Value *v){v2=v;}
  void CalculateResult(){result=GetOp()->Calculate1(GetV1Value(), GetV2Value());}
  virtual void Print()=0;
  virtual MathOperation *New()=0;
  virtual void Type()=0;
  virtual void Calculate()=0;
  virtual ~MathOperation()
  {
    cout<<"~MathOperation()"<<'\n';
    delete v1;
    delete v2;
    delete math_operator;
    delete next;

    // while(this->next!=nullptr)
    //   {
    // 	cout<<"next->next!=nullptr"<<'\n';
    // 	next=next->next;
    //   }
  }
};

class MMMathOperation: public MathOperation
{
   // Math-math math operation
public:
  Value *v1_2=nullptr;
  Value *v2_2=nullptr;
  MathOperator *math_operator_2=nullptr;
  double result2=NAN;

  MathOperator *math_operator_3=nullptr;
  double total_result=NAN;

  void SetOperator2(const string &s)
  {
    if(s==ADD) math_operator_3=new Add;
    else if(s==SUBTRACT) math_operator_3=new Sub;
    else if(s==MULTIPLY) math_operator_3=new Mul;
    else if(s==DIVIDE) math_operator_3=new Div;
    else if(s==EXP) math_operator_3=new Exp;
  }
  void Print()
  {
    // cout<<"MMMathOperation mo1 "<<this<<" v1 "<<mo1->v1<<" mo "<<mo1->math_operator<<" v2 "<<mo1->v2<<'\n';
    // cout<<"MMMathOperation mo2 "<<this<<" v1 "<<mo2->v1<<" mo "<<mo2->math_operator<<" v2 "<<mo2->v2<<'\n';
  }
  ~MMMathOperation()
  {
    cout<<"~MMMathOperation()"<<'\n';
    delete v1_2;
    delete v2_2;
    delete math_operator_3;
    delete math_operator_2;
    cout<<" "<<'\n';
  }
  MathOperation *New()
  {
    MathOperation *n=new MMMathOperation;
    return n;
  }
  void Calculate()
  {
    CalculateResult();
    cout<<"result calculated "<<result<<'\n';
  }
  void Type(){cout<<"Type is MMMath"<<'\n';}
};

class NMMathOperation: public MathOperation
{
  // Numeric-math math operation
public:
  void Print(){}
  MathOperation *New()
  {
    MathOperation *n=new NMMathOperation;
    return n;
  }
  void Type(){cout<<"Type is NMMath"<<'\n';}
  void Calculate()
  {
    CalculateResult();
    cout<<"result calculated "<<result<<'\n';
  }
};

class MVMathOperation: public MathOperation
{
  // Math-variable math operation
public:
  // Value *v1_v=nullptr;

  // Value *v1_2=nullptr;
  // Value *v2_2=nullptr;
  // MathOperator *math_operator_2=nullptr;
  // double result2=NAN;

  // void SetOperator2(const string &s)
  // {
  //   if(s==ADD) math_operator_3=new Add;
  //   else if(s==SUBTRACT) math_operator_3=new Sub;
  //   else if(s==MULTIPLY) math_operator_3=new Mul;
  //   else if(s==DIVIDE) math_operator_3=new Div;
  //   else if(s==EXP) math_operator_3=new Exp;
  // }

  void Print(){}
  MathOperation *New()
  {
    MathOperation *n=new MVMathOperation;
    return n;
  }
  void Calculate(){}
  void Type(){cout<<"Type is MVMath"<<'\n';}
};

class CMMathOperation: public MathOperation
{
  // Constant-math math operation
public:
  void Print(){}
  MathOperation *New()
  {
    MathOperation *n=new CMMathOperation;
    return n;
  }
  void Calculate(){}
  void Type(){cout<<"Type is CMMath"<<'\n';}
};

class NNMathOperation: public MathOperation
{
  // Numeric-numeric math operation
public:
  void Print(){}
  MathOperation *New()
  {
    MathOperation *n=new NNMathOperation;
    return n;
  }
  void Calculate(){CalculateResult();}
  void Type(){cout<<"Type is NNMath"<<'\n';}
};

class VVMathOperation: public MathOperation
{
  // Variable-variable math operation
private:
  Value *v1;
  Value *v2;
  MathOperator *math_operator;
public:
  int id;
  double result=NAN;

  void Print()
  {
    cout<<"VVMathOperation "<<this<<" v1 "<<this->GetV1()<<" mo "<<this->GetOp()<<" v2 "<<this->GetV2()<<'\n';
  }
  ~VVMathOperation()=default;
  MathOperation *New()
  {
    MathOperation *n=new VVMathOperation;
    return n;
  }
  void Calculate(){}
  void Type(){cout<<"Type is VVMath"<<'\n';}
};

class CVMathOperation: public MathOperation
{
  // Constant-variable math operation
public:
  void Print(){}
  MathOperation *New()
  {
    MathOperation *n=new CVMathOperation;
    return n;
  }
  void Calculate(){}
  void Type(){cout<<"Type is CVMath"<<'\n';}
};

class CCMathOperation: public MathOperation
{
  // Constant-constant math operation
public:
  void Print(){}
  MathOperation *New()
  {
    MathOperation *n=new CCMathOperation;
    return n;
  }
  void Calculate(){}
  void Type(){cout<<"Type is CCMath"<<'\n';}
};

class NVMathOperation: public MathOperation
{
  // Numeric-variable math operation
public:
  void Print(){}
  MathOperation *New()
  {
    MathOperation *n=new NVMathOperation;
    return n;
  }
  void Calculate(){}
  void Type(){cout<<"Type is NVMath"<<'\n';}
};

class NCMathOperation: public MathOperation
{
  // Numeric-constant math operation
public:
  void Print(){}
  MathOperation *New()
  {
    MathOperation *n=new NCMathOperation;
    return n;
  }
  void Calculate(){}
  void Type(){cout<<"Type is NCMath"<<'\n';}
};

#endif
