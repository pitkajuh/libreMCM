#ifndef MATHOPERATOR_H
#define MATHOPERATOR_H

#include <cmath>

class MathOperator
{
public:
  MathOperator(){}
  virtual double Calculate(const double v1, const double v2)=0;
  virtual ~MathOperator(){}
};

class Add:public MathOperator
{
public:
  double Calculate(const double v1, const double v2){return v1+v2;}
  Add(){}
  ~Add(){}
};

class Sub:public MathOperator
{
public:
  double Calculate(const double v1, const double v2){return v1-v2;}
  Sub(){}
  ~Sub(){}
};

class Mul:public MathOperator
{
public:
  double Calculate(const double v1, const double v2){return v1*v2;}
  Mul(){}
  ~Mul(){}
};

class Div:public MathOperator
{
public:
  double Calculate(const double v1, const double v2){return v1/v2;}
  Div(){}
  ~Div(){}
};

class Exp:public MathOperator
{
public:
  double Calculate(const double v1, const double v2){return pow(v1, v2);}
  Exp(){}
  ~Exp(){}
};

#endif
