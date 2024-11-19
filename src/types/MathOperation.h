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

using namespace libremcm;

class MathOperationBase
{
protected:
  Value *v1=nullptr;
public:
  double result=NAN;
  Value *&GetV1(){return v1;}
  double GetV1Value(){return v1->GetValue();} const
  string GetV1Name(){return v1->GetName();} const
  void SetV1(Value *v){v1=v;}
  void Calculate(){result=GetV1Value();}
  MathOperationBase(){}
  MathOperationBase(const MathOperationBase &m)
  {
    // v1=new MathOperationBase;
    cout<<"MathOperationBase copy"<<'\n';
    this->v1=m.v1;
  }
  virtual void SetValue(SMap &ValueMap)=0;
  virtual ~MathOperationBase(){delete v1;}
};

class NumericBase: public MathOperationBase
{
  // Numeric math operation
public:
  void SetValue(SMap &ValueMap){}
};

class VariableBase: public MathOperationBase
{
  // Variable math operation
public:
  void SetValue(SMap &ValueMap){}
};

class ConstantBase: public MathOperationBase
{
  // Constant math operation
public:
  void SetValue(SMap &ValueMap)
  {
    // cout<<"SetValue "<<std::stod(ValueMap[v1->GetName()])<<'\n';
    cout<<"SetValue "<<'\n';
    v1->SetValue(std::stod(ValueMap[v1->GetName()]));
    Calculate();
  }
};

class MathOperation: public MathOperationBase
{
protected:
  Value *v2=nullptr;
  MathOperator *math_operator=nullptr;
public:
  void SetValue(SMap &ValueMap)
  {
    cout<<"MathOperation SetValue"<<'\n';
    // cout<<"SetValue "<<std::stod(ValueMap[v2->GetName()])<<'\n';
    // v2->SetValue(std::stod(ValueMap[v2->GetName()]));
  }
  void SetOperator(const string &s)
  {
    if(s==ADD) math_operator=new Add;
    else if(s==SUBTRACT) math_operator=new Sub;
    else if(s==MULTIPLY) math_operator=new Mul;
    else if(s==DIVIDE) math_operator=new Div;
    else if(s==EXP) math_operator=new Exp;
  }
  MathOperator *&GetMathOperator(){return math_operator;}
  Value *&GetV2(){return v2;}
  double GetV2Value(){return v2->GetValue();} const
  string GetV2Name(){return v2->GetName();} const
  void SetV2(Value *v){v2=v;}
  void Calculate(){result=math_operator->Calculate(GetV1Value(), GetV2Value());}
  MathOperation(){}
  MathOperation(const MathOperation &m)
  {
    // v1=new MathOperationBase;
    cout<<"MathOperation copy"<<'\n';
    this->v1=m.v1;
    this->v2=m.v2;
    this->math_operator=m.math_operator;
  }
  ~MathOperation()
  {
    delete v2;
    delete math_operator;
  }
};

class NumericNumeric: public MathOperation
{
  // Numeric-numeric math operation
public:
  void SetValue(SMap &ValueMap){}
};

class VariableVariable: public MathOperation
{
  // Variable-variable math operation
public:
  void SetValue(SMap &ValueMap){}
};

class ConstantVariable: public MathOperation
{
  // Constant-variable math operation
public:
  ConstantVariable(){}
  ConstantVariable(MathOperation &m)
  {
    // v1=new MathOperationBase;
    cout<<"ConstantVariable copy"<<'\n';
    this->v1=m.GetV1();
    this->v2=m.GetV2();
    this->math_operator=m.GetMathOperator();
  }
  void SetValue(SMap &ValueMap)
  {
    cout<<"SetValue ConstantVariable "<<std::stod(ValueMap[v1->GetName()])<<'\n';
    v1->SetValue(std::stod(ValueMap[v1->GetName()]));
  }
};

class VariableConstant: public MathOperation
{
  // Variable-constant math operation
public:
  void SetValue(SMap &ValueMap)
  {
    cout<<"SetValue VariableConstant "<<std::stod(ValueMap[v2->GetName()])<<'\n';
    v2->SetValue(std::stod(ValueMap[v2->GetName()]));
  }
};

class ConstantConstant: public MathOperation
{
  // Constant-constant math operation
public:
  void SetValue(SMap &ValueMap)
  {
    cout<<"SetValue ConstantConstant "<<v1->GetName()<<" "<<std::stod(ValueMap[v1->GetName()])<<" "<<v2->GetName()<<" "<<std::stod(ValueMap[v2->GetName()])<<'\n';
    v1->SetValue(std::stod(ValueMap[v1->GetName()]));
    v2->SetValue(std::stod(ValueMap[v2->GetName()]));
    Calculate();
    cout<<"result "<<result<<'\n';
  }
};

class VariableNumeric: public MathOperation
{
  // Variable-numeric math operation
public:
  void SetValue(SMap &ValueMap){}
};

class NumericVariable: public MathOperation
{
  // Numeric-variable math operation
public:
  void SetValue(SMap &ValueMap){}
};

class NumericConstant: public MathOperation
{
  // Numeric-constant math operation
public:
  void SetValue(SMap &ValueMap)
  {
    cout<<"SetValue "<<std::stod(ValueMap[v2->GetName()])<<'\n';
    v2->SetValue(std::stod(ValueMap[v2->GetName()]));
    Calculate();
    cout<<"result "<<result<<'\n';
  }
};

class ConstantNumeric: public MathOperation
{
  // Constant-numeric math operation
public:
  void SetValue(SMap &ValueMap)
  {
    cout<<"SetValue "<<std::stod(ValueMap[v1->GetName()])<<'\n';
    v1->SetValue(std::stod(ValueMap[v1->GetName()]));
    Calculate();
    cout<<"result "<<result<<'\n';
  }
};

#endif
