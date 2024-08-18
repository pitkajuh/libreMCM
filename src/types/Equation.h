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

class EquationBase
{
public:
  unsigned int id;
  double result=NAN;
  virtual void Calculate()=0;
};

class Equation: public EquationBase
{
public:
  MathOperation *m1;
  Equation *next=nullptr;
  void Calculate()
  {
    m1->CalculateResult();
  }
  void Type()
  {
    cout<<"Equation"<<'\n';
  };
  virtual ~Equation()
  {
    cout<<"~Equation "<<this<<'\n';
    cout<<"Deleting m1 "<<m1<<'\n';
    delete m1;
    cout<<"m1 deleted"<<'\n';
    cout<<"Deleting next "<<next<<'\n';
    delete next;
    cout<<"next deleted"<<'\n';
  }
};

class EquationOp: public Equation
{
public:
  MathOperation *m2;
  MathOperator *math_operator;
  void Calculate()
  {
    m1->CalculateResult();
    m2->CalculateResult();
    result=math_operator->Calculate1(m1->result, m2->result);
  }
  void SetOperator(const string &s)
  {
    if(s==ADD) math_operator=new Add;
    else if(s==SUBTRACT) math_operator=new Sub;
    else if(s==MULTIPLY) math_operator=new Mul;
    else if(s==DIVIDE) math_operator=new Div;
    else if(s==EXP) math_operator=new Exp;
  }
  void Type()
  {
    cout<<"EquationOp"<<'\n';
  }
  ~EquationOp()
  {
    cout<<"~EquationOP "<<this<<'\n';
    cout<<"Deleting m2 "<<m2<<'\n';
    delete m2;
    cout<<"m2 deleted"<<'\n';
    cout<<"Deleting math_operator "<<math_operator<<'\n';
    delete math_operator;
    cout<<"math_operator deleted"<<'\n';
  }
};

class EquationV: public Equation
{
public:
  Value *v;
  MathOperator *math_operator1;
  void Calculate()
  {
    m1->CalculateResult();
    result=math_operator1->Calculate1(m1->result, v->GetValue());
  }
  void SetOperator(const string &s)
  {
    if(s==ADD) math_operator1=new Add;
    else if(s==SUBTRACT) math_operator1=new Sub;
    else if(s==MULTIPLY) math_operator1=new Mul;
    else if(s==DIVIDE) math_operator1=new Div;
    else if(s==EXP) math_operator1=new Exp;
  }
  void Type()
  {
    cout<<"EquationV"<<'\n';
  }
  ~EquationV()
  {
    cout<<"~EquationV "<<this<<'\n';
    cout<<"Deleting v "<<v<<'\n';
    delete v;
    cout<<"v deleted"<<'\n';
    cout<<"Deleting math_operator1 "<<math_operator1<<'\n';
    delete math_operator1;
    cout<<"math_operator1 deleted"<<'\n';
  }
};

class VEquation: public EquationV
{
    void Type()
  {
    cout<<"VEquation"<<'\n';
  }
  void Calculate()
  {
    m1->CalculateResult();
    result=math_operator1->Calculate1(v->GetValue(), m1->result);
  }
};

#endif
