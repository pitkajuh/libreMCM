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

class Equation
{
public:
  int id;
  MathOperation *m1;
  double result=NAN;
  Equation *next=nullptr;
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
    // next=nullptr;
    cout<<"next deleted"<<'\n';
  }
};

class EquationOp: public Equation
{
public:
  MathOperation *m2;
  MathOperator *math_operator;
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

#endif
