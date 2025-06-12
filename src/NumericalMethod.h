#ifndef NUMERICALMETHOD_H
#define NUMERICALMETHOD_H

class NumericalMethod
{
public:
  double *currentValues=nullptr;

  NumericalMethod(){}
  virtual ~NumericalMethod(){}
};

class RungeKutta4: public NumericalMethod
{
public:

  RungeKutta4(){}
  ~RungeKutta4(){}
};

#endif
