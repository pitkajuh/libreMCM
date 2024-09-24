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
public:
  uint8_t id;
  double result=NAN;
  virtual void Calculate()=0;
};

class Equation: public EquationBase
{
public:
  MathOperation *m1=nullptr;
  Equation *next=nullptr;
  MathOperator *math_operator=nullptr;

  void SetOperator(const string &s)
  {
    if(s==ADD) math_operator=new Add;
    else if(s==SUBTRACT) math_operator=new Sub;
    else if(s==MULTIPLY) math_operator=new Mul;
    else if(s==DIVIDE) math_operator=new Div;
    else if(s==EXP) math_operator=new Exp;
  }

  void Calculate()
  {
    // m1->CalculateResult();
    // result=m1->result;
  }
  Equation *New()
  {
    printf("new Equation\n");
    return new Equation;
  }
  virtual ~Equation()
  {
    delete m1;
    delete math_operator;
  }
};

class EquationValue: public Equation
{
public:
  Equation *m11=nullptr;
  Value *v=nullptr;

  void CalculateResult(const double result)
  {
    // m1->CalculateResult();
    // result=m1->result;
    // result=math_operator->Calculate1(v->GetValue(), d);
  }
  void Calculate()
  {
    // m1->CalculateResult();
    // result=m1->result;
    // result=math_operator->Calculate1(v->GetValue(), m1->result);
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
  void CalculateResult(const double d)
  {
    // m1->CalculateResult();
    // result=m1->result;
    result=math_operator->Calculate1(d, v->GetValue());
  }
  void Calculate()
  {
    // m1->CalculateResult();
    // result=m1->result;
    // result=math_operator->Calculate1(v->GetValue(), m1->result);
  }
  EquationV *New()
  {
    printf("new EquationV\n");
    return new EquationV;
  }
};

class VEquation: public EquationValue
{
public:
  void CalculateResult(const double d)
  {
    // m1->CalculateResult();
    // result=m1->result;
    result=math_operator->Calculate1(v->GetValue(), d);
  }
  void Calculate()
  {
    // m1->CalculateResult();
    // result=m1->result;
    // result=math_operator->Calculate1(v->GetValue(), m1->result);
  }
  VEquation *New()
  {
    printf("new VEquation\n");
    return new VEquation;
  }
};

class EquationMath: public Equation
{
public:
  Equation *m11=nullptr;
  Equation *m21=nullptr;

  void SetMath(Equation *&m, const uint8_t i, const uint8_t j)
  {
    Equation *c=m;

    while(c!=nullptr)
      {
	if(c->id==i) m11=c;
	c=c->next;
      }

    c=m;

    while(c!=nullptr)
      {
	if(c->id==i) m21=c;
	c=c->next;
      }
  }
  void Calculate()
  {
    // m1->CalculateResult();
    // result=m1->result;
  }
  EquationMath *New()
  {
    printf("new EquationMath\n");
    return new EquationMath;
  }
  virtual ~EquationMath()
  {
    delete m11;
    delete m21;
  }
};

#endif
