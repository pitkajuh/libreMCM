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
  MathOperationBase(MathOperationBase &m)
  {
    cout<<"MathOperationBase copy"<<'\n';
    this->result=m.result;
    this->v1=m.GetV1()->New(*m.GetV1());
  }
  MathOperationBase &operator=(MathOperationBase &m)
  {
    std:: cout<<"MathOperationBase ="<<'\n';
    if(this==&m) return *this;

    return *this;
  }
  virtual MathOperationBase *clone() {return new MathOperationBase(*this);}
  virtual void SetValue(SMap &ValueMap){};
  virtual MathOperationBase *New(MathOperationBase &m) const {return new MathOperationBase(m);}
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
  MathOperationBase *New(MathOperationBase &m) const {return new NumericBase(m);}
  NumericBase *clone() override {return new NumericBase(*this);}
  NumericBase &operator=(MathOperationBase &m)
  {
    std:: cout<<"NumericBase ="<<'\n';
    if(this==&m) return *this;

    this->v1=new Numeric(*m.GetV1());

    return *this;
  }
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
  MathOperationBase *New(MathOperationBase &m) const {return new VariableBase(m);}
  VariableBase *clone() override {return new VariableBase(*this);}
  VariableBase &operator=(MathOperationBase &m)
  {
    std:: cout<<"VariableBase ="<<'\n';
    if(this==&m) return *this;

    this->v1=new Variable(*m.GetV1());

    return *this;
  }
};

class ConstantBase: public MathOperationBase
{
  // Constant math operation
public:
  void SetValue(SMap &ValueMap)
  {
    v1->SetValue(std::stod(ValueMap[v1->GetName()]));
    Calculate();
  }
  ConstantBase(){}
  ConstantBase(MathOperationBase &m)
  {
    cout<<" ConstantBase copy"<<'\n';
    this->v1=new Constant(*m.GetV1());
  }
  MathOperationBase *New(MathOperationBase &m) const {return new ConstantBase(m);}
  ConstantBase *clone() override {return new ConstantBase(*this);}
  ConstantBase &operator=(MathOperationBase &m)
  {
    std:: cout<<"ConstantBase ="<<'\n';
    if(this==&m) return *this;

    this->v1=new Constant(*m.GetV1());

    return *this;
  }
};

class MathOperation: public MathOperationBase
{
protected:
  Value *v2=nullptr;
  MathOperator *math_operator=nullptr;
public:
  void SetValue(SMap &ValueMap){}
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
  MathOperation(const MathOperation &m){}
  MathOperation *clone() override {return new MathOperation(*this);}
  MathOperationBase *New(MathOperationBase &m) const {return new MathOperation(m);}
  MathOperation &operator=(MathOperation &m)
  {
    if(this==&m) return *this;

    return *this;
  }
  ~MathOperation()
  {
    delete v2;
    cout<<"delete math_operator "<<math_operator<<'\n';
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
    this->math_operator=m.GetMathOperator()->New();
  }
  NumericNumeric *clone() override {return new NumericNumeric(*this);}
  MathOperationBase *New(MathOperationBase &m) const {return new NumericNumeric(m);}
  NumericNumeric &operator=(MathOperation &m)
  {
    std:: cout<<"NumericNumeric ="<<'\n';
    if(this==&m) return *this;

    this->v1=new Numeric(*m.GetV1());
    this->v2=new Numeric(*m.GetV2());
    this->math_operator=m.GetMathOperator()->New();

    return *this;
  }
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
  VariableVariable *clone() override {return new VariableVariable(*this);}
  MathOperationBase *New(MathOperationBase &m) const {return new VariableVariable(m);}
  VariableVariable &operator=(MathOperation &m)
  {
    std:: cout<<"VariableVariable ="<<'\n';
    if(this==&m) return *this;

    this->v1=new Variable(*m.GetV1());
    this->v2=new Variable(*m.GetV2());
    this->math_operator=m.GetMathOperator()->New();

    return *this;
  }
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
    this->math_operator=m.GetMathOperator()->New();
  }
  ConstantVariable *clone() override {return new ConstantVariable(*this);}
  MathOperationBase *New(MathOperationBase &m) const {return new ConstantVariable(m);}
  ConstantVariable &operator=(MathOperation &m)
  {
    std:: cout<<"ConstantVariable ="<<'\n';
    if(this==&m) return *this;

    this->v1=new Constant(*m.GetV1());
    this->v2=new Variable(*m.GetV2());
    this->math_operator=m.GetMathOperator()->New();

    return *this;
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
  VariableConstant(){}
  VariableConstant(MathOperation &m)
  {
    cout<<"VariableConstant copy"<<'\n';
    this->v1=new Variable(*m.GetV1());
    this->v2=new Constant(*m.GetV2());
    this->math_operator=m.GetMathOperator()->New();
  }
  VariableConstant *clone() override {return new VariableConstant(*this);}
  MathOperationBase *New(MathOperationBase &m) const {return new VariableConstant(m);}
  VariableConstant &operator=(MathOperation &m)
  {
    std:: cout<<"VariableConstant ="<<'\n';
    if(this==&m) return *this;

    this->v1=new Variable(*m.GetV1());
    this->v2=new Constant(*m.GetV2());
    this->math_operator=m.GetMathOperator()->New();

    return *this;
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
  ConstantConstant(){}
  ConstantConstant(MathOperation &m)
  {
    cout<<"ConstantConstant copy"<<'\n';
    cout<<"copy v1"<<'\n';
    this->v1=new Constant(*m.GetV1());
    cout<<"copy v2"<<'\n';
    this->v2=new Constant(*m.GetV2());
     this->math_operator=m.GetMathOperator()->New();
     cout<<m.GetMathOperator()<<" "<<GetMathOperator()<<'\n';

  }
  ConstantConstant *clone() override {return new ConstantConstant(*this);}
  MathOperationBase *New(MathOperationBase &m) const {return new ConstantConstant(m);}
  ConstantConstant &operator=(MathOperation &m)
  {
    std:: cout<<"ConstantConstant ="<<'\n';
    if(this==&m) return *this;

    this->v1=new Constant(*m.GetV1());
    this->v2=new Constant(*m.GetV2());
    this->math_operator=m.GetMathOperator()->New();

    return *this;
  }
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
    this->math_operator=m.GetMathOperator()->New();
  }
  VariableNumeric *clone() override {return new VariableNumeric(*this);}
  MathOperationBase *New(MathOperationBase &m) const {return new VariableNumeric(m);}
  VariableNumeric &operator=(MathOperation &m)
  {
    std:: cout<<"VariableNumeric ="<<'\n';
    if(this==&m) return *this;

    this->v1=new Variable(*m.GetV1());
    this->v2=new Numeric(*m.GetV2());
    this->math_operator=m.GetMathOperator()->New();

    return *this;
  }
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
    this->math_operator=m.GetMathOperator()->New();
  }
  NumericVariable *clone() override {return new NumericVariable(*this);}
  MathOperationBase *New(MathOperationBase &m) const {return new NumericVariable(m);}
  NumericVariable &operator=(MathOperation &m)
  {
    std:: cout<<"NumericVariable ="<<'\n';
    if(this==&m) return *this;

    this->v1=new Numeric(*m.GetV1());
    this->v2=new Variable(*m.GetV2());
    this->math_operator=m.GetMathOperator()->New();

    return *this;
  }
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
    this->math_operator=m.GetMathOperator()->New();
  }
  NumericConstant *clone() override {return new NumericConstant(*this);}
  MathOperationBase *New(MathOperationBase &m) const {return new NumericConstant(m);}
  NumericConstant &operator=(MathOperation &m)
  {
    std:: cout<<"NumericConstant ="<<'\n';
    if(this==&m) return *this;

    this->v1=new Numeric(*m.GetV1());
    this->v2=new Variable(*m.GetV2());
    this->math_operator=m.GetMathOperator()->New();

    return *this;
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
  ConstantNumeric(){}
  ConstantNumeric(MathOperation &m)
  {
    cout<<"ConstantNumeric copy"<<'\n';
    this->v1=new Constant(*m.GetV1());
    this->v2=new Numeric(*m.GetV2());
    this->math_operator=m.GetMathOperator()->New();
  }
  ConstantNumeric *clone() override {return new ConstantNumeric(*this);}
  MathOperationBase *New(MathOperationBase &m) const {return new ConstantNumeric(m);}
  ConstantNumeric &operator=(MathOperation &m)
  {
    std:: cout<<"ConstantNumeric ="<<'\n';
    if(this==&m) return *this;

    this->v1=new Constant(*m.GetV1());
    this->v2=new Numeric(*m.GetV2());
    this->math_operator=m.GetMathOperator()->New();

    return *this;
  }
};

#endif
