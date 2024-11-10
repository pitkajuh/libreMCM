/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef EQUATION_H
#define EQUATION_H

#include "MathOperation.h"
#include "MathOperator.h"
#include <cstdint>

class EquationBase
{
private:
  uint8_t id;
public:
  double result=NAN;
  void SetId(const uint8_t id1){id=id1;}
  const uint8_t GetId(){return id;}
  virtual void SetValue(SMap &ValueMap)=0;
  virtual void Calculate()=0;
  virtual void GetType()=0;
  virtual void Print()=0;
};

class Equation: public EquationBase
{
protected:
  MathOperator *math_operator=nullptr;
  MathOperation *m1=nullptr;
public:
  Equation *next=nullptr;

  void SetValue(SMap &ValueMap)
  {
    cout<<this<<" SetValue "<<"Equation"<<'\n';
    // cout<<"Setting "<<this<<" "<<m1<<" "<<std::to_string(GetId())<<'\n';
    if(m1!=nullptr) m1->SetValue(ValueMap);
  }

  MathOperation *&GetMathOperation(){return m1;}
  void SetOperator(const string &s)
  {
    if(s==ADD) math_operator=new Add;
    else if(s==SUBTRACT) math_operator=new Sub;
    else if(s==MULTIPLY) math_operator=new Mul;
    else if(s==DIVIDE) math_operator=new Div;
    else if(s==EXP) math_operator=new Exp;
  }
  void Calculate(){result=m1->result;}
  void Print()
  {
    cout<<"Equation"<<'\n';
  }
  void GetType()
  {
    printf("new normal Equation\n");
  }
  virtual ~Equation()
  {
    cout<<"Deleting "<<this<<" "<<std::to_string(GetId())<<'\n';
    delete m1;
    delete math_operator;
  }
};

class EquationValue: public Equation
{
protected:
  Equation *m11=nullptr;
  Value *v=nullptr;
public:
  void SetValue(SMap &ValueMap)
  {
    cout<<"SetValue "<<"EquationValue"<<'\n';
    m11->SetValue(ValueMap);
    // v->SetValue(std::stod(ValueMap[v->GetName()]));
  }
  Value *GetValue(){return v;}
  void Set(Equation *m0){m11=m0;}
  void SetValue(Value *w){v=w;}
  Equation *&Get(){return m11;}
  void Print()
  {
    cout<<"Equation"<<'\n';
  }
  void GetType()
  {
    printf("new EquationValue\n");
  }
  virtual ~EquationValue()
  {
    delete m11;
    delete v;
  }
};

class EquationV: public EquationValue
{
public:
  void Calculate(){result=math_operator->Calculate(GetValue()->GetValue(), Get()->result);}
  void SetValue(SMap &ValueMap)
  {
    cout<<"SetValue "<<"EquationV"<<'\n';
    m11->SetValue(ValueMap);
  }
  void Print()
  {
    cout<<"Equation"<<'\n';
  }
  void GetType()
  {
    printf("new EquationV\n");
  }
};

class EquationVNumerical: public EquationV
{
public:
  void SetValue(SMap &ValueMap)
  {
    cout<<"new EquationVNumerical SetValue "<<'\n';
    m11->SetValue(ValueMap);
  }
};

class EquationVConstant: public EquationV
{
public:
  void SetValue(SMap &ValueMap)
  {
    cout<<this<<" EquationVConstant SetValue "<<v->GetName()<<" "<<std::stod(ValueMap[v->GetName()])<<" "<<next<<'\n';
    v->SetValue(std::stod(ValueMap[v->GetName()]));
    m11->SetValue(ValueMap);
  }
};

class EquationVVariable: public EquationV
{
public:
  void SetValue(SMap &ValueMap)
  {
    cout<<this<<" EquationVVariable SetValue "<<'\n';
    m11->SetValue(ValueMap);
  }
};

class VEquation: public EquationValue
{
public:
  void Calculate(){result=math_operator->Calculate(GetValue()->GetValue(), Get()->result);}
  void SetValue(SMap &ValueMap)
  {
    cout<<"VEquation SetValue "<<'\n';
    m11->SetValue(ValueMap);
  }
  void Print()
  {
    cout<<"Equation"<<'\n';
  }
  void GetType()
  {
    printf("new VEquation\n");
  }
};

class VEquationNumerical: public VEquation
{
public:
  void SetValue(SMap &ValueMap)
  {
    cout<<"VEquationNumerical SetValue "<<'\n';
    m11->SetValue(ValueMap);
  }
};

class VEquationConstant: public VEquation
{
public:
  void SetValue(SMap &ValueMap)
  {
    cout<<this<<" VEquationConstant SetValue "<<v->GetName()<<" "<<std::stod(ValueMap[v->GetName()])<<" "<<next<<'\n';
    v->SetValue(std::stod(ValueMap[v->GetName()]));
    m11->SetValue(ValueMap);
  }
};

class VEquationVariable: public VEquation
{
public:
  void SetValue(SMap &ValueMap)
  {
    cout<<"VEquationVariable SetValue "<<'\n';
    m11->SetValue(ValueMap);
  }
};

class EquationMath: public Equation
{
protected:
  Equation *m11=nullptr;
  Equation *m21=nullptr;
public:
  void SetValue(SMap &ValueMap)
  {
    m11->SetValue(ValueMap);
    m21->SetValue(ValueMap);
  }
  Equation *&GetM1(){return m11;}
  Equation *&GetM2(){return m21;}
  void Set(Equation *m1, Equation *m2)
  {
    cout<<"Equation *m1, Equation *m2"<<'\n';
    m11=m1;
    m21=m2;
  }
  void Calculate(){result=math_operator->Calculate(m11->result, m21->result);}
  void Print()
  {
    cout<<"Equation"<<'\n';
  }
  void GetType()
  {
    printf("new EquationMath\n");
  }
  virtual ~EquationMath()
  {
    delete m11;
    delete m21;
  }
};

#endif
