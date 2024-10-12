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
protected:
  uint8_t id;
public:
  double result=NAN;
  void SetId(const uint8_t id1){id=id1;}
  const uint8_t GetId(){return id;}
  virtual void Calculate()=0;
  virtual void GetType()=0;
};

class Equation: public EquationBase
{
protected:
  MathOperator *math_operator=nullptr;
public:
  MathOperation *m1=nullptr;
  Equation *next=nullptr;

  void SetOperator(const string &s)
  {
    if(s==ADD) math_operator=new Add;
    else if(s==SUBTRACT) math_operator=new Sub;
    else if(s==MULTIPLY) math_operator=new Mul;
    else if(s==DIVIDE) math_operator=new Div;
    else if(s==EXP) math_operator=new Exp;
  }
  void Calculate(){result=m1->result;}
  void GetType()
  {
    printf("new normal Equation\n");
  }
  virtual ~Equation()
  {
    delete m1;
    delete math_operator;
  }
};

class EquationValue: public Equation
{
private:
  Equation *m11=nullptr;
  Value *v=nullptr;
public:
  Value *GetValue(){return v;}
  void Set(Equation *m0){m11=m0;}
  void SetValue(Value *w){v=w;}
  Equation *&Get(){return m11;}
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
  void GetType()
  {
    printf("new EquationV\n");
  }
};

class VEquation: public EquationValue
{
public:
  void Calculate(){result=math_operator->Calculate(GetValue()->GetValue(), Get()->result);}
  void GetType()
  {
    printf("new VEquation\n");
  }
};

class EquationMath: public Equation
{
private:
  Equation *m11=nullptr;
  Equation *m21=nullptr;
public:
  Equation *&GetM1(){return m11;}
  Equation *&GetM2(){return m21;}
  void Set(Equation *m1, Equation *m2)
  {
    m11=m1;
    m21=m2;
  }
  void Calculate(){result=math_operator->Calculate(m11->result, m21->result);}
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
