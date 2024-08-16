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
  double result;
  Equation *next=nullptr;
  virtual ~Equation()
  {
    delete m1;
    delete next;
  }
};

class EquationOp: public Equation
{
public:
  MathOperation *m2;
  MathOperator *math_operator;
  ~EquationOp()
  {
    delete m2;
    delete math_operator;
  }
};

#endif
