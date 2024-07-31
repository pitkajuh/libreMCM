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

#include <math.h>
#include "../global/mathconst.h"

class MathOperator
{
public:
  virtual double Calculate1(const double &v1, const double &v2)=0;
  virtual MathOperator *New()=0;
};

class Add:public MathOperator
{
public:
  double Calculate1(const double &v1, const double &v2) {return v1+v2;}
  MathOperator *New()
  {
    MathOperator *m=new Add;
    return m;
  }
};

class Sub:public MathOperator
{
public:
  double Calculate1(const double &v1, const double &v2) {return v1-v2;}
  MathOperator *New()
  {
    MathOperator *m=new Sub;
    return m;
  }
};

class Mul:public MathOperator
{
public:
  double Calculate1(const double &v1, const double &v2) {return v1*v2;}
  MathOperator *New()
  {
    MathOperator *m=new Mul;
    return m;
  }
};

class Div:public MathOperator
{
public:
  double Calculate1(const double &v1, const double &v2) {return v1/v2;}
  MathOperator *New()
  {
    MathOperator *m=new Div;
    return m;
  }
};

class Exp:public MathOperator
{
public:
  double Calculate1(const double &v1, const double &v2) {return pow(v1, v2);}
  MathOperator *New()
  {
    MathOperator *m=new Exp;
    return m;
  }
};

#endif
