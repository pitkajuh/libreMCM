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

class EquationOperation
{
public:
  double result=NAN;
  MathOperation *m1=nullptr;
  MathOperator *math_operator=nullptr;

  void SetOperator(const string &s)
  {
    if(s==ADD) math_operator=new Add;
    else if(s==SUBTRACT) math_operator=new Sub;
    else if(s==MULTIPLY) math_operator=new Mul;
    else if(s==DIVIDE) math_operator=new Div;
    else if(s==EXP) math_operator=new Exp;
  }
  void Calculate(){}
  virtual ~EquationOperation()
  {
    delete m1;
    delete math_operator;
  }
};

class EquationOperationOp: public EquationOperation
{
public:
  MathOperation *m2=nullptr;

  void Calculate()
  {
    m1->CalculateResult();
    m2->CalculateResult();
    result=math_operator->Calculate1(m1->result, m2->result);
  }
  ~EquationOperationOp(){delete m2;}
};

class EquationOperationValueBase: public EquationOperation
{
public:
  Value *v=nullptr;

  virtual void CalculateResult(const double d)=0;
  ~EquationOperationValueBase(){delete v;}
};

class EquationOperationValue: public EquationOperationValueBase
{
public:
  void CalculateResult(const double d)
  {
    result=math_operator->Calculate1(d, v->GetValue());
  }
  void Calculate()
  {
    m1->CalculateResult();
    result=math_operator->Calculate1(m1->result, v->GetValue());
  }
};

class ValueEquationOperation: public EquationOperationValueBase
{
  void CalculateResult(const double d)
  {
    result=math_operator->Calculate1(v->GetValue(), d);
  }
  void Calculate()
  {
    m1->CalculateResult();
    result=math_operator->Calculate1(v->GetValue(), m1->result);
  }
};

class EquationBase
{
public:
  uint8_t id;
  double result=NAN;
  virtual void Calculate()=0;
};

class EquationBase2: public EquationBase
{
public:
  MathOperator *math_operator=nullptr;

  void SetOperator(const string &s)
  {
    if(s==ADD) math_operator=new Add;
    else if(s==SUBTRACT) math_operator=new Sub;
    else if(s==MULTIPLY) math_operator=new Mul;
    else if(s==DIVIDE) math_operator=new Div;
    else if(s==EXP) math_operator=new Exp;
  }
  virtual ~EquationBase2(){delete math_operator;}
};

class Equation: public EquationBase2
{
public:
  EquationOperation *m1=nullptr;
  Equation *next=nullptr;

  void Calculate()
  {
    // m1->CalculateResult();
    // result=m1->result;
  }
  virtual ~Equation(){delete m1;}
};

class EquationMath: public Equation
{
public:
  Equation *m11=nullptr;
  Equation *m21=nullptr;

  void Calculate()
  {
    // m1->CalculateResult();
    // result=m1->result;
  }
  virtual ~EquationMath()
  {
    delete m11;
    delete m21;
  }
};

#endif
