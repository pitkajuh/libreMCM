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

class MathOperationBase
{
public:
  int id;
  double result=NAN;
  // MathOperationBase *next=nullptr;

  virtual void Type()=0;
  virtual ~MathOperationBase()
  {
    cout<<"~MathOperationBase()"<<'\n';
    // delete next;
  }
};

class MathOperation: public MathOperationBase
{
private:
  Value *v1=nullptr;
  Value *v2=nullptr;
  MathOperator *math_operator=nullptr;
public:
  MathOperation *next=nullptr;

  void SetOperator(const string &s)
  {
    if(s==ADD) math_operator=new Add;
    else if(s==SUBTRACT) math_operator=new Sub;
    else if(s==MULTIPLY) math_operator=new Mul;
    else if(s==DIVIDE) math_operator=new Div;
    else if(s==EXP) math_operator=new Exp;
  }
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
  void SetV1Name(const string &s){v1->SetName(s);} const
  void SetV2Name(const string &s){v2->SetName(s);} const
  void SetV1(Value *v){v1=v;}
  void SetV2(Value *v){v2=v;}
  void CalculateResult(){result=math_operator->Calculate1(GetV1Value(), GetV2Value());}
  ~MathOperation()
  {
    cout<<"~MathOperation()"<<'\n';
    delete v1;
    delete v2;
    delete math_operator;
    delete next;
  }
  virtual void Type()=0;
};

class ValueMath: public MathOperation
{
private:
  Value *v;
  MathOperator *math_operator1=nullptr;
public:
  double result_total=NAN;

  void SetOperator1(const string &s)
  {
    if(s==ADD) math_operator1=new Add;
    else if(s==SUBTRACT) math_operator1=new Sub;
    else if(s==MULTIPLY) math_operator1=new Mul;
    else if(s==DIVIDE) math_operator1=new Div;
    else if(s==EXP) math_operator1=new Exp;
  }
  MathOperator *GetOp(){return math_operator1;} const
  void SetV(Value *v1){v=v1;}
  Value *GetV(){return v;} const
  double GetVValue(){return v->GetValue();} const
  string GetVName(){return v->GetName();} const
  void SetVName(const string &s){v->SetName(s);}
  void SetVValue(const double &d){v->SetValue(d);}
  ~ValueMath()
  {
    cout<<"~ValueMath()"<<'\n';
    delete v;
    delete math_operator1;
  }
  void Type()
  {
    cout<<"ValueMath()"<<'\n';
  }
};

class MathMath: public MathOperation
{
   // Math-math math operation
private:
  Value *v1_2;
  Value *v2_2;
  MathOperator *math_operator_2;
  MathOperator *total_math_operator;

public:
  double result2=NAN;
  double total_result=NAN;

  void SetV12(Value *v){v1_2=v;}
  void SetV22(Value *v){v2_2=v;}
  Value *GetV12(){return v1_2;}
  Value *GetV22(){return v2_2;} const
  double GetV12Value(){return v1_2->GetValue();} const
  double GetV22Value(){return v2_2->GetValue();} const
  string GetV1Name(){return v1_2->GetName();} const
  string GetV2Name(){return v2_2->GetName();} const
  void SetV21Value(const double &d){v1_2->SetValue(d);} const
  void SetV22Value(const double &d){v2_2->SetValue(d);} const
  void SetV12Name(const string &s){v1_2->SetName(s);} const
  void SetV22Name(const string &s){v2_2->SetName(s);} const
  void SetOperator2(MathOperator *m){math_operator_2=m;}
  void SetTotalOperator(const string &s)
  {
    if(s==ADD) total_math_operator=new Add;
    else if(s==SUBTRACT) total_math_operator=new Sub;
    else if(s==MULTIPLY) total_math_operator=new Mul;
    else if(s==DIVIDE) total_math_operator=new Div;
    else if(s==EXP) total_math_operator=new Exp;
  }
  void Print()
  {
    // cout<<"MathMath mo1 "<<this<<" v1 "<<mo1->v1<<" mo "<<mo1->math_operator<<" v2 "<<mo1->v2<<'\n';
    // cout<<"MathMath mo2 "<<this<<" v1 "<<mo2->v1<<" mo "<<mo2->math_operator<<" v2 "<<mo2->v2<<'\n';
  }
  ~MathMath()
  {
    cout<<"~MathMath()"<<'\n';
    delete v1_2;
    delete v2_2;
    delete total_math_operator;
    delete math_operator_2;
    cout<<" "<<'\n';
  }
  MathOperationBase *New()
  {
    MathOperationBase *n=new MathMath;
    return n;
  }
  void Calculate()
  {
    // CalculateResult();
    // cout<<"result calculated "<<result<<'\n';
  }
  void Type(){cout<<"Type is MMMath"<<'\n';}
};

class NumericMath: public ValueMath
{
  // Numeric-math math operation
public:
  void Print(){}
  MathOperationBase *New()
  {
    MathOperationBase *n=new NumericMath;
    return n;
  }
  void Type(){cout<<"Type is NMMath"<<'\n';}
  void Calculate()
  {
    // CalculateResult();
    // cout<<"result calculated "<<result<<'\n';
  }
};

class MathVariable: public ValueMath
{
  // Math-variable math operation
public:
  void Print(){}
  MathOperationBase *New()
  {
    MathOperationBase *n=new MathVariable;
    return n;
  }
  void Type(){cout<<"Type is MVMath"<<'\n';}
};

class ConstantMath: public MathOperationBase
{
  // Constant-math math operation
public:
  void Print(){}
  MathOperationBase *New()
  {
    MathOperationBase *n=new ConstantMath;
    return n;
  }
  void Type(){cout<<"Type is CMMath"<<'\n';}
};

class NumericNumeric: public MathOperation
{
  // Numeric-numeric math operation
public:
  void Print(){}
  MathOperationBase *New()
  {
    MathOperationBase *n=new NumericNumeric;
    return n;
  }
  void Type(){cout<<"Type is NNMath"<<'\n';}
};

class VariableVariable: public MathOperation
{
  // Variable-variable math operation
public:
  void Print()
  {
    // cout<<"VariableVariable "<<this<<" v1 "<<this->GetV1()<<" mo "<<this->GetOp()<<" v2 "<<this->GetV2()<<'\n';
  }
  MathOperationBase *New()
  {
    MathOperationBase *n=new VariableVariable;
    return n;
  }
  void Type(){cout<<"Type is VariableVariable"<<'\n';}
};

class ConstantVariable: public MathOperation
{
  // Constant-variable math operation
public:
  void Print(){}
  MathOperationBase *New()
  {
    MathOperationBase *n=new ConstantVariable;
    return n;
  }
  void Calculate(){}
  void Type(){cout<<"Type is CVMath"<<'\n';}
};

class ConstantConstant: public MathOperation
{
  // Constant-constant math operation
public:
  void Print(){}
  MathOperationBase *New()
  {
    MathOperationBase *n=new ConstantConstant;
    return n;
  }
  void Calculate(){}
  void Type(){cout<<"Type is CCMath"<<'\n';}
};

class NumericVariable: public MathOperation
{
  // Numeric-variable math operation
public:
  void Print(){}
  MathOperationBase *New()
  {
    MathOperationBase *n=new NumericVariable;
    return n;
  }
  void Calculate(){}
  void Type(){cout<<"Type is NVMath"<<'\n';}
};

class NumericConstant: public MathOperation
{
  // Numeric-constant math operation
public:
  void Print(){}
  MathOperationBase *New()
  {
    MathOperationBase *n=new NumericConstant;
    return n;
  }
  void Calculate(){}
  void Type(){cout<<"Type is NCMath"<<'\n';}
};

#endif
