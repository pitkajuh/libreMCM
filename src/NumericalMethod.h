#ifndef NUMERICALMETHOD_H
#define NUMERICALMETHOD_H

class NumericalMethod
{
public:
  double *currentValues=nullptr;

  NumericalMethod(){}
  virtual ~NumericalMethod(){delete [] currentValues;}
};

class RungeKutta4: public NumericalMethod
{
public:

  RungeKutta4(){}
  RungeKutta4(const uint16_t N){currentValues=new double[N];}
  ~RungeKutta4(){}
};

#endif
