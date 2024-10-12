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

class MathOperator
{
public:
  virtual double Calculate(const double v1, const double v2)=0;
  virtual MathOperator *New()=0;
  virtual ~MathOperator(){}
};

class Add:public MathOperator
{
public:
  double Calculate(const double v1, const double v2){return v1+v2;}
  MathOperator *New(){return new Add;}
};

class Sub:public MathOperator
{
public:
  double Calculate(const double v1, const double v2){return v1-v2;}
  MathOperator *New(){return new Sub;}
};

class Mul:public MathOperator
{
public:
  double Calculate(const double v1, const double v2){return v1*v2;}
  MathOperator *New(){return new Mul;}
};

class Div:public MathOperator
{
public:
  double Calculate(const double v1, const double v2){return v1/v2;}
  MathOperator *New(){return new Div;}
};

class Exp:public MathOperator
{
public:
  double Calculate(const double v1, const double v2){return pow(v1, v2);}
  MathOperator *New(){return new Exp;}
};

#endif
