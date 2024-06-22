/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef MATHOPERATOR_H
#define MATHOPERATOR_H

#include "Value.h"
// #include "../global/matrix.h"
#include "../global/mathconst.h"
// #include "../util/is_in_vector.h"

class MathOperator
{
public:
  virtual double Calculate(const double v1, const double v2)=0;
  ~MathOperator(){}
};

class Add:public MathOperator
{
public:
  double Calculate(const double v1, const double v2) {return v1+v2;}
};

class Sub:public MathOperator
{
public:
  double Calculate(const double v1, const double v2) {return v1-v2;}
};

class Mul:public MathOperator
{
public:
  double Calculate(const double v1, const double v2) {return v1*v2;}
};

class Div:public MathOperator
{
public:
  double Calculate(const double v1, const double v2) {return v1/v2;}
};

class Exp:public MathOperator
{
public:
  double Calculate(const double v1, const double v2) {return pow(v1, v2);}
};

#endif
