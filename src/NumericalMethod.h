#ifndef NUMERICALMETHOD_H
#define NUMERICALMETHOD_H

class NumericalMethod
{
public:
  double *currentValues=nullptr;

  NumericalMethod(){}
  virtual void Calculate(const uint16_t timeStart, const uint16_t timeEnd, const uint16_t stepSize, const vector<Edge> &edges)=0;
  virtual ~NumericalMethod(){delete [] currentValues;}
};

class RungeKutta4: public NumericalMethod
{
public:
  void Calculate(const uint16_t timeStart, const uint16_t timeEnd, const uint16_t stepSize, const vector<Edge> &edges)
  {
    for(const Edge &e: edges)
      {
	cout<<e.from<<" "<<e.to<<'\n';
      }
  }

  RungeKutta4(){}
  RungeKutta4(const uint16_t N){currentValues=new double[N];}
  ~RungeKutta4(){}
};

#endif
