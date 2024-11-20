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
//   MathOperator(){}
//   MathOperator(const MathOperator &m)
//   {
//     // return new MathOperator(*m);
//     // return this;
// }
//   // virtual MathOperator *clone() const {return new MathOperator(*this);}
//   virtual MathOperator *clone()=0;
  virtual double Calculate(const double v1, const double v2)=0;
  virtual MathOperator *New()=0;
  virtual ~MathOperator(){}
};

class Add:public MathOperator
{
public:
  double Calculate(const double v1, const double v2){return v1+v2;}
  MathOperator *New(){return new Add;}
  // Add(){}
  // Add(const MathOperator &m)
  // {
  //   return new Add(*m);
  // }
  // Add *clone() override {return new Add(*this);}
};

class Sub:public MathOperator
{
public:
  double Calculate(const double v1, const double v2){return v1-v2;}
  MathOperator *New(){return new Sub;}
  // Sub(){}
  // Sub(const MathOperator &m)
  // {
  //   return new Sub(*m);
  // }
  // Sub *clone() override {return new Sub(*this);}
};

class Mul:public MathOperator
{
public:
  double Calculate(const double v1, const double v2){return v1*v2;}
  MathOperator *New(){return new Mul;}
  // Mul(){}
  // Mul(const MathOperator &m)
  // {
  //   return new Mul(*m);
  // }
  // Mul *clone() override {return new Mul(*this);}
};

class Div:public MathOperator
{
public:
  double Calculate(const double v1, const double v2){return v1/v2;}
  MathOperator *New(){return new Div;}
  // Div(){}
  // Div(const MathOperator &m)
  // {
  //   return new Div(*m);
  // }
  // Div *clone() override {return new Div(*this);}
};

class Exp:public MathOperator
{
public:
  double Calculate(const double v1, const double v2){return pow(v1, v2);}
  MathOperator *New(){return new Exp;}
  // Exp(){}
  // Exp(const MathOperator &m)
  // {
  //   return new Exp(*m);
  // }
  // Exp *clone() override {return new Exp(*this);}
};

#endif
