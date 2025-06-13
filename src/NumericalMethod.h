#ifndef NUMERICALMETHOD_H
#define NUMERICALMETHOD_H

class NumericalMethod
{
public:
  double *currentValues=nullptr;
  // vector<double> currentValues;

  NumericalMethod(){}
  // virtual ~NumericalMethod(){delete [] currentValues;}
  virtual ~NumericalMethod(){}
};

class RungeKutta4: public NumericalMethod
{
public:

  RungeKutta4(){}
  RungeKutta4(const uint16_t N){currentValues=new double[N];}
  // RungeKutta4(const uint16_t N){currentValues.reserve(N);}
  ~RungeKutta4(){}
};

#endif
