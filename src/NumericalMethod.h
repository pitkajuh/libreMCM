#ifndef NUMERICALMETHOD_H
#define NUMERICALMETHOD_H

class NumericalMethod
{
public:
  double *results=nullptr;
  double *currentValues=nullptr;
  vector<uint16_t> noOfInitialValue;
  uint16_t timeStart=0;
  uint16_t timeEnd=0;
  uint16_t stepSize=0;

  NumericalMethod(){}
  virtual void Calculate(const uint16_t timeStart, const uint16_t timeEnd, const uint16_t stepSize, const vector<Edge> &edges, const vector<uint16_t> &noOfInitialValue)=0;
  virtual ~NumericalMethod()
  {
    delete [] currentValues;
    delete [] results;
  }
};

class RungeKutta4: public NumericalMethod
{
private:
  void k()
  {

  }

  void RK4()
  {
    uint16_t t=stepSize;

    while(t<=timeEnd)
      {
	cout<<"t="<<t<<'\n';
	// k1=;
	// k2=;
	// k3=;
	// k4=;

	t+=stepSize;
      }
  }
public:
  void Calculate(const uint16_t timeStart, const uint16_t timeEnd, const uint16_t stepSize, const vector<Edge> &edges, const vector<uint16_t> &noOfInitialValue)
  {
    this->noOfInitialValue=noOfInitialValue;
    this->timeStart=timeStart;
    this->timeEnd=timeEnd;
    this->stepSize=stepSize;

    for(const Edge &e: edges)
      {
	cout<<"From "<<e.from<<" To "<<e.to<<'\n';
	RK4();
	break;
      }
  }

  RungeKutta4(){}
  RungeKutta4(const uint16_t N){currentValues=new double[N];}
  ~RungeKutta4(){}
};

#endif
