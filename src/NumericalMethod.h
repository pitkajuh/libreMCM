#ifndef NUMERICALMETHOD_H
#define NUMERICALMETHOD_H

class NumericalMethod
{
public:
  double *results=nullptr;
  double *currentValues=nullptr;
  double *newValues=nullptr;
  vector<uint16_t> noOfInitialValue;
  uint16_t timeStart=0;
  uint16_t timeEnd=0;
  uint16_t stepSize=0;
  uint16_t N=0;

  NumericalMethod(){}
  virtual void Calculate(const uint16_t timeStart, const uint16_t timeEnd, const uint16_t stepSize, const vector<Edge> &edges, const vector<uint16_t> &noOfInitialValue)=0;
  virtual ~NumericalMethod()
  {
    delete [] newValues;
    delete [] currentValues;
    delete [] results;
  }
};

class RungeKutta4: public NumericalMethod
{
private:
  void k(const uint16_t from, const uint16_t to, Equation *equation, double *k, const double constant, double *kPrevious)
  {
    // Replace values in currentValues

    for(uint16_t i=0; i<N; i++)
      {
	currentValues[i]=currentValues[i]+constant*kPrevious[i];
      }

    for(uint16_t i=0; i<N; i++)
      {
	k[i]=stepSize*equation->Calculate();
      }

    // copy from newValues to currentValues
    cout<<" "<<'\n';
    for(uint16_t i=0; i<N; i++)
      {
	currentValues[i]=newValues[i];
      }
  }

  void k0(Equation *equation, double *k)
  {
    for(uint16_t i=0; i<N; i++)
      {
	k[i]=stepSize*equation->Calculate();
      }
  }

  void RK4(const uint16_t from, const uint16_t to, Equation *equation)
  {
    uint16_t t=stepSize;
    double *k1=new double[N];
    double *k2=new double[N];
    double *k3=new double[N];
    double *k4=new double[N];
    double *r=new double[N];

    while(t<=timeEnd)
      {
	cout<<"t="<<t<<" "<<from<<" "<<to<<'\n';
	k0(equation, k1);
	k(from, to, equation, k2, 0.5, k1);
	k(from, to, equation, k3, 0.5, k2);
	k(from, to, equation, k4, 1, k3);

	for(uint16_t i=0; i<N; i++)
	  {
	    r[i]=currentValues[i]+stepSize*(k1[i]+2*k2[i]+2*k3[i]+k4[i])/6;
	    currentValues[i]=r[i];
	  }

	t+=stepSize;
      }
    delete [] k1;
    delete [] k2;
    delete [] k3;
    delete [] k4;
    delete [] r;
  }
public:
  void Calculate(const uint16_t timeStart, const uint16_t timeEnd, const uint16_t stepSize, const vector<Edge> &edges, const vector<uint16_t> &noOfInitialValue)
  {
    std::copy(currentValues, currentValues+N, newValues);
    this->noOfInitialValue=noOfInitialValue;
    this->timeStart=timeStart;
    this->timeEnd=timeEnd;
    this->stepSize=stepSize;

    for(const Edge &e: edges)
      {
	cout<<"From "<<e.from<<" To "<<e.to<<'\n';
	RK4(e.from, e.to, e.equation);
	break;
      }
  }

  RungeKutta4(){}
  RungeKutta4(const uint16_t N)
  {
    this->N=N;
    cout<<"N "<<N<<'\n';
    currentValues=new double[N];
    newValues=new double[N];
  }
  ~RungeKutta4(){}
};

#endif
