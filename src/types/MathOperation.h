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
  double result=NAN;

  virtual void Type()=0;
  virtual ~MathOperationBase()
  {
    // cout<<"~MathOperationBase() "<<this<<'\n';
  }
};

class MathOperation: public MathOperationBase
{
private:
  Value *v1;
  Value *v2;
  MathOperator *math_operator;
public:
  void SetOperator(const string &s)
  {
    if(s==ADD) math_operator=new Add;
    else if(s==SUBTRACT) math_operator=new Sub;
    else if(s==MULTIPLY) math_operator=new Mul;
    else if(s==DIVIDE) math_operator=new Div;
    else if(s==EXP) math_operator=new Exp;
  }
  double GetV1Value(){return v1->GetValue();} const
  double GetV2Value(){return v2->GetValue();} const
  string GetV1Name(){return v1->GetName();} const
  string GetV2Name(){return v2->GetName();} const
  void SetV1(Value *v){v1=v;}
  void SetV2(Value *v){v2=v;}
  void CalculateResult(){result=math_operator->Calculate1(GetV1Value(), GetV2Value());}
  ~MathOperation()
  {
    // cout<<"~MathOperation() "<<this<<'\n';
    // cout<<"Trying to delete v1 "<<v1<<'\n';
    delete v1;
    // cout<<"v1 deleted"<<'\n';
    // cout<<"Trying to delete v2 "<<v2<<'\n';
    delete v2;
    // cout<<"v2 deleted"<<'\n';
    // cout<<"Trying to delete math_operator "<<math_operator<<'\n';
    delete math_operator;
    // cout<<"math_operator deleted"<<'\n';

    // cout<<"Trying to delete next "<<next<<'\n';
    // delete next;
    // cout<<"next deleted"<<'\n';
    cout<<" "<<'\n';

  }
  virtual void Type()=0;
};

class ValueMath: public MathOperation
{
private:
  Value *v;
  MathOperator *math_operator1;
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
  MathOperator *GetOp1(){return math_operator1;} const
  void SetV(Value *v1){v=v1;}
  Value *GetV(){return v;} const
  double GetVValue(){return v->GetValue();} const
  string GetVName(){return v->GetName();} const
  void SetVName(const string &s){v->SetName(s);}
  void SetVValue(const double &d){v->SetValue(d);}
  ~ValueMath()
  {
    // cout<<"~ValueMath() "<<this<<'\n';
    // cout<<"Trying to delete v "<<v<<'\n';
    delete v;
    // cout<<"v deleted"<<'\n';
    // cout<<"Trying to delete math_operator1 "<<math_operator1<<'\n';
    delete math_operator1;
    // cout<<"math_operator1 deleted"<<'\n';
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
    // cout<<"~MathMath() "<<this<<'\n';
    // cout<<"Trying to delete v1_2 "<<v1_2<<'\n';
    delete v1_2;
    // cout<<"v1_2 deleted"<<'\n';
    // cout<<"Trying to delete v2_2 "<<v2_2<<'\n';
    delete v2_2;
    // cout<<"v2_2 deleted"<<'\n';
    // cout<<"Trying to delete total_math_operator "<<total_math_operator<<'\n';
    delete total_math_operator;
    // cout<<"total_math_operator deleted"<<'\n';
    // cout<<"Trying to delete math_operator_2 "<<math_operator_2<<'\n';
    delete math_operator_2;
    // cout<<"math_operator_2 deleted"<<'\n';
    // cout<<" "<<'\n';
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
