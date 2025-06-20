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
  virtual void Calculate(const uint16_t timeStart, const uint16_t timeEnd, const uint16_t stepSize, const vector<Edge> &edges, const vector<uint16_t> &noOfInitialValue, Equations &equations)=0;
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
  void k(Equation &equation, double *&k, const double constant, const double *kPrevious)
  {
    // Replace values in currentValues

    for(uint16_t i=0; i<N; i++)
      {
	currentValues[i]=currentValues[i]+constant*kPrevious[i];
      }

    for(uint16_t i=0; i<N; i++)
      {
	k[i]=stepSize*equation.Calculate();
      }

    // copy from newValues to currentValues

    for(uint16_t i=0; i<N; i++)
      {
	currentValues[i]=newValues[i];
      }
  }

  void k0(Equation &equation, double *&k)
  {
    for(uint16_t i=0; i<N; i++)
      {
	k[i]=stepSize*equation.Calculate();
      }
  }

  void RK4(const vector<Edge> &edges, Equations &equations)
  {
    uint16_t t=stepSize;
    uint16_t n=1;
    const uint16_t N2=equations.equations.size()*(timeEnd-timeStart)/stepSize;
    double *k1=new double[N];
    double *k2=new double[N];
    double *k3=new double[N];
    double *k4=new double[N];
    double *r=new double[N2];
    // double *r=new double[N];
    cout<<N<<" "<<N2<<'\n';
    // while(t<=timeEnd)
    while(n<=(timeEnd-timeStart)/stepSize)
      {
	// cout<<"t="<<t<<'\n';

	for(Equation &equation: equations.equations)
	  {
	    k0(equation, k1);
	    k(equation, k2, 0.5, k1);
	    k(equation, k3, 0.5, k2);
	    k(equation, k4, 1, k3);
	    string aa;
	    for(uint16_t i=0; i<N; i++)
	      {
		// cout<<k1[i]<<"+"<<2*k2[i]<<"+"<<2*k3[i]<<"+"<<k4[i]<<"="<<k1[i]+2*k2[i]+2*k3[i]+k4[i]<<'\n';
		r[i]=currentValues[i]+stepSize*(k1[i]+2*k2[i]+2*k3[i]+k4[i])/6;
		// cout<<r[i]<<'\n';
		currentValues[i]=r[i];
		aa+=std::to_string(r[i]);
		aa+=";";
	      }

	    cout<<aa<<'\n';
	  }

	for(const Edge &e: edges)
	  {
	    // cout<<e.from<<" "<<e.to<<'\n';
	  }

	t+=stepSize;
	n++;
      }

    delete [] k1;
    delete [] k2;
    delete [] k3;
    delete [] k4;
    delete [] r;
  }
public:
  void Calculate(const uint16_t timeStart, const uint16_t timeEnd, const uint16_t stepSize, const vector<Edge> &edges, const vector<uint16_t> &noOfInitialValue, Equations &equations)
  {
    std::copy(currentValues, currentValues+N, newValues);
    this->noOfInitialValue=noOfInitialValue;
    this->timeStart=timeStart;
    this->timeEnd=timeEnd;
    this->stepSize=stepSize;

    RK4(edges, equations);

    // for(const Edge &e: edges)
    //   {
    // 	cout<<"From "<<e.from<<" To "<<e.to<<'\n';
    // 	RK4(e.from, e.to, e.equation);
    // 	break;
    //   }
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
