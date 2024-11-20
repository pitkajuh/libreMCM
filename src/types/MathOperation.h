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
    cout<<"MathOperationBase copy"<<'\n';
    this->v1=new Value(*m.v1);
  }
  virtual MathOperationBase *clone() const {return new MathOperationBase(*this);}
  virtual void SetValue(SMap &ValueMap){};
  virtual ~MathOperationBase(){delete v1;}
};

class NumericBase: public MathOperationBase
{
  // Numeric math operation
public:
  void SetValue(SMap &ValueMap){}
  NumericBase(){}
  NumericBase(MathOperationBase &m)
  {
    cout<<" NumericBase copy"<<'\n';
    this->v1=new Numeric(*m.GetV1());
  }
  NumericBase *clone() const override {return new NumericBase(*this);}
};

class VariableBase: public MathOperationBase
{
  // Variable math operation
public:
  void SetValue(SMap &ValueMap){}
  VariableBase(){}
  VariableBase(MathOperationBase &m)
  {
    cout<<" VariableBase copy"<<'\n';
    this->v1=new Variable(*m.GetV1());
  }
  VariableBase *clone() const override {return new VariableBase(*this);}
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
  ConstantBase(){}
  ConstantBase(MathOperationBase &m)
  {
    cout<<" ConstantBase copy"<<'\n';
    this->v1=new Constant(*m.GetV1());
  }
  ConstantBase *clone() const override {return new ConstantBase(*this);}
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
    cout<<"MathOperation copy"<<'\n';
  }
  MathOperation *clone() const override {return new MathOperation(*this);}
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
  NumericNumeric(){}
  NumericNumeric(MathOperation &m)
  {
    cout<<"NumericNumeric copy"<<'\n';
    this->v1=new Numeric(*m.GetV1());
    this->v2=new Numeric(*m.GetV2());
    this->math_operator=m.GetMathOperator();
  }
  NumericNumeric *clone() const override {return new NumericNumeric(*this);}
};

class VariableVariable: public MathOperation
{
  // Variable-variable math operation
public:
  void SetValue(SMap &ValueMap){}
  VariableVariable(){}
  VariableVariable(MathOperation &m)
  {
    cout<<"VariableVariable copy"<<'\n';
    this->v1=new Variable(*m.GetV1());
    this->v2=new Variable(*m.GetV2());
    this->math_operator=m.GetMathOperator();
  }
  VariableVariable *clone() const override {return new VariableVariable(*this);}
};

class ConstantVariable: public MathOperation
{
  // Constant-variable math operation
public:
  void SetValue(SMap &ValueMap)
  {
    cout<<"SetValue ConstantVariable "<<std::stod(ValueMap[v1->GetName()])<<'\n';
    v1->SetValue(std::stod(ValueMap[v1->GetName()]));
  }
  ConstantVariable(){}
  ConstantVariable(MathOperation &m)
  {
    cout<<"ConstantVariable copy"<<'\n';
    this->v1=new Constant(*m.GetV1());
    this->v2=new Variable(*m.GetV2());
    this->math_operator=m.GetMathOperator();
  }
  ConstantVariable *clone() const override {return new ConstantVariable(*this);}
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
  VariableConstant(){}
  VariableConstant(MathOperation &m)
  {
    cout<<"VariableConstant copy"<<'\n';
    this->v1=new Variable(*m.GetV1());
    this->v2=new Constant(*m.GetV2());
    this->math_operator=m.GetMathOperator();
  }
  VariableConstant *clone() const override {return new VariableConstant(*this);}
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
  ConstantConstant(){}
  ConstantConstant(MathOperation &m)
  {
    cout<<"ConstantConstant copy"<<'\n';
    this->v1=new Constant(*m.GetV1());
    this->v2=new Constant(*m.GetV2());
    this->math_operator=m.GetMathOperator();
  }
  ConstantConstant *clone() const override {return new ConstantConstant(*this);}
};

class VariableNumeric: public MathOperation
{
  // Variable-numeric math operation
public:
  void SetValue(SMap &ValueMap){}
  VariableNumeric(){}
  VariableNumeric(MathOperation &m)
  {
    cout<<"VariableNumeric copy"<<'\n';
    this->v1=new Variable(*m.GetV1());
    this->v2=new Numeric(*m.GetV2());
    this->math_operator=m.GetMathOperator();
  }
  VariableNumeric *clone() const override {return new VariableNumeric(*this);}
};

class NumericVariable: public MathOperation
{
  // Numeric-variable math operation
public:
  void SetValue(SMap &ValueMap){}
  NumericVariable(){}
  NumericVariable(MathOperation &m)
  {
    cout<<"NumericVariable copy"<<'\n';
    this->v1=new Numeric(*m.GetV1());
    this->v2=new Variable(*m.GetV2());
    this->math_operator=m.GetMathOperator();
  }
  NumericVariable *clone() const override {return new NumericVariable(*this);}
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
  NumericConstant(){}
  NumericConstant(MathOperation &m)
  {
    cout<<"NumericConstant copy"<<'\n';
    this->v1=new Numeric(*m.GetV1());
    this->v2=new Variable(*m.GetV2());
    this->math_operator=m.GetMathOperator();
  }
  NumericConstant *clone() const override {return new NumericConstant(*this);}
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
  ConstantNumeric(){}
  ConstantNumeric(MathOperation &m)
  {
    cout<<"ConstantNumeric copy"<<'\n';
    this->v1=new Constant(*m.GetV1());
    this->v2=new Numeric(*m.GetV2());
    this->math_operator=m.GetMathOperator();
  }
  ConstantNumeric *clone() const override {return new ConstantNumeric(*this);}
};

#endif
