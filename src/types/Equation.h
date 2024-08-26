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
  unsigned id;
  double result=NAN;
  virtual void Calculate()=0;
};

class Equation: public EquationBase
{
public:
  MathOperation *m1=nullptr;
  MathOperator *math_operator=nullptr;
  Equation *next=nullptr;

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
    m1->CalculateResult();
    result=m1->result;
  }
  void Type()
  {
    cout<<"Equation"<<'\n';
  }
  virtual ~Equation()
  {
    cout<<"~Equation "<<this<<" "<<id<<'\n';
    // cout<<"Deleting m1 "<<m1<<'\n';
    delete m1;
    // cout<<"m1 deleted"<<'\n';
    // cout<<"Deleting next "<<next<<'\n';
    // delete next;
    // cout<<"next deleted"<<'\n';
    delete math_operator;
    cout<<"~Equation ok"<<'\n';
  }
};

class Equation1: public Equation
{
public:
  MathOperator *math_operator1=nullptr;
  Equation *m12=nullptr;
  Equation *m22=nullptr;
  Equation *next=nullptr;

  void SetOperator(const string &s)
  {
    if(s==ADD) math_operator=new Add;
    else if(s==SUBTRACT) math_operator=new Sub;
    else if(s==MULTIPLY) math_operator=new Mul;
    else if(s==DIVIDE) math_operator=new Div;
    else if(s==EXP) math_operator=new Exp;
  }
  ~Equation1()
  {
    cout<<"~Equation1 "<<this<<" "<<id<<'\n';
    delete m12;
    delete m22;
    delete math_operator1;
  }
};

class EquationOp: public Equation
{
public:
  MathOperation *m2=nullptr;

  void Calculate()
  {
    m1->CalculateResult();
    m2->CalculateResult();
    result=math_operator->Calculate1(m1->result, m2->result);
  }
  void Type()
  {
    cout<<"EquationOp"<<'\n';
  }
  ~EquationOp()
  {
    cout<<"~EquationOP "<<this<<" "<<id<<'\n';
    // cout<<"Deleting m2 "<<m2<<'\n';
    delete m2;
    // cout<<"m2 deleted"<<'\n';
    // cout<<"Deleting math_operator "<<math_operator<<'\n';
    // delete math_operator;
    // cout<<"math_operator deleted"<<'\n';
    cout<<"~EquationOP ok"<<'\n';
  }
};

class EquationValueBase: public Equation
{
public:
  Value *v=nullptr;

  virtual void CalculateResult(const double &d)=0;
  void Type(){cout<<"EquationV"<<'\n';}
  ~EquationValueBase()
  {
    cout<<"~EquationV "<<this<<" "<<id<<'\n';
    // cout<<"Deleting v "<<v<<'\n';
    delete v;
    // cout<<"v deleted"<<'\n';
    // cout<<"Deleting math_operator1 "<<math_operator1<<'\n';
    // delete math_operator1;
    // cout<<"math_operator1 deleted"<<'\n';
    cout<<"~EquationV  ok"<<'\n';
  }
};

class EquationValue: public EquationValueBase
{
public:
  void CalculateResult(const double &d)
  {
    cout<<"EquationV"<<'\n';
    result=math_operator->Calculate1(d, v->GetValue());
  }
  void Calculate()
  {
    m1->CalculateResult();
    result=math_operator->Calculate1(m1->result, v->GetValue());
  }
};

class ValueEquation: public EquationValueBase
{
  void CalculateResult(const double &d)
  {
    cout<<"VEquation"<<'\n';
    result=math_operator->Calculate1(v->GetValue(), d);
  }
  void Calculate()
  {
    m1->CalculateResult();
    result=math_operator->Calculate1(v->GetValue(), m1->result);
  }
};

#endif
