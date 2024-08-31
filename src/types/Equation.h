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

  virtual void CalculateResult(const double &d)=0;
  ~EquationOperationValueBase(){delete v;}
};

class EquationOperationValue: public EquationOperationValueBase
{
public:
  void CalculateResult(const double &d)
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
  void CalculateResult(const double &d)
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
  unsigned id;
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
  virtual ~EquationBase2()
  {
    cout<<"~EquationBase2 "<<this<<" "<<id<<'\n';
    delete math_operator;
    cout<<"~EquationBase2 ok"<<'\n';
  }
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
  virtual ~Equation()
  {
    cout<<"~Equation "<<this<<" "<<id<<'\n';
    delete m1;
    cout<<"~Equation ok"<<'\n';
  }
};

// class EquationOp: public Equation
// {
// public:
//   EquationOperation *m2=nullptr;

//   void Calculate()
//   {
//     // m1->CalculateResult();
//     // m2->CalculateResult();
//     // result=math_operator->Calculate1(m1->result, m2->result);
//   }
//   ~EquationOp()
//   {
//     cout<<"~EquationOP "<<this<<" "<<id<<'\n';
//     // cout<<"Deleting m2 "<<m2<<'\n';
//     delete m2;
//     // cout<<"m2 deleted"<<'\n';
//     // cout<<"Deleting math_operator "<<math_operator<<'\n';
//     // delete math_operator;
//     // cout<<"math_operator deleted"<<'\n';
//     cout<<"~EquationOP ok"<<'\n';
//   }
// };

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
    cout<<"~EquationMath "<<this<<" "<<id<<'\n';

    // m11->next=nullptr;
    // m21->next=nullptr;
    cout<<"deleting m11"<<'\n';
    delete m11;
    cout<<"m11 ok"<<'\n';
    cout<<"deleting m21"<<'\n';
    delete m21;
    cout<<"m21 ok"<<'\n';
    // this->next=nullptr;
    // next->next=nullptr;
    // next=nullptr;

    cout<<"~EquationMath ok "<<this<<'\n';
    cout<<"---------------------------------------------------"<<'\n';
  }
};

#endif
