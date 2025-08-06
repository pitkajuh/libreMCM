#ifndef NUMERICALMETHOD_H
#define NUMERICALMETHOD_H

class NumericalMethod
{
public:
  double *y_np1=nullptr;
  double *y_n=nullptr;
  double *newValues=nullptr;
  double *valuesSubstitute=nullptr;
  uint16_t timeStart=0;
  uint16_t timeEnd=0;
  uint16_t stepSize=0;
  uint16_t nx=0;
  uint16_t N=0;
  uint16_t ny=0;
  uint16_t nValue=0;
  // uint16_t from=0;
  // uint16_t to=0;
  // uint16_t delta=0;

  NumericalMethod(){}
  virtual void Calculate(const uint16_t timeStart, const uint16_t timeEnd, const uint16_t stepSize, vector<Edge> &edges, Equations &equations, const uint16_t N, const vector<uint16_t> &noOfInitialValue)=0;
  virtual ~NumericalMethod()
  {
    delete [] newValues;
    delete [] y_n;
    delete [] y_np1;
    delete [] valuesSubstitute;
  }
};

class RungeKutta4: public NumericalMethod
{
private:
  void print(const double *k, const uint16_t from, const uint16_t to)
  {
    string a;

    for(uint16_t i=from; i<to; i++)
      {
	a+=std::to_string(k[i])+";";
      }
    cout<<a<<'\n';
  }

  void EquationSubstitute1(const uint16_t from, const uint16_t to, const double *kFrom, double *kTo)
  {
    for(uint16_t i=from; i<to; i++)
      {
	// cout<<"i="<<i<<" "<<kFrom[i]<<'\n';
	kTo[i-from]=kFrom[i];
      }
  }

  void k(vector<Edge> &equation, double *&k, const double constant, double *kPrevious)
  {
    for(uint16_t i=0; i<nValue; i++)
      {
	// cout<<"subs "<<valuesSubstitute[i]<<"+"<<constant<<"*"<<kPrevious[i]<<"="<<valuesSubstitute[i]+constant*kPrevious[i]<<'\n';
	// const double a=valuesSubstitute[i]+constant*kPrevious[i];
	const double a=this->y_n[i]+constant*kPrevious[i];
	valuesSubstitute[i]=a;
	// valuesSubstitute[i]=+constant*kPrevious[i];
	cout<<"now "<<valuesSubstitute[i]<<'\n';
      }

    // EquationSubstitute1(0, this->nValue, k, this->valuesSubstitute);

    for(uint16_t i=0; i<equation.size(); i++)
      {
	auto a1=equation[i].Calculate();
	k[i]=this->stepSize*a1;
	cout<<i<<" k1 "<<stepSize<<"*"<<a1<<"="<<k[i]<<'\n';
      }
    // cout<<" "<<'\n';

    for(uint16_t j=this->nValue; j<this->nx; j+=this->nValue)
      {
	// cout<<"j="<<j<<"/"<<this->nx-1<<'\n';

	EquationSubstitute1(j, j+this->nValue, kPrevious, this->valuesSubstitute);

	for(uint16_t i=0; i<equation.size(); i++)
	  {
	    auto a1=equation[i].Calculate();
	    // k[i]=stepSize*equation.Calculate();
	    k[i+j]=this->stepSize*a1;
	    // cout<<i+j<<" k1 "<<stepSize<<"*"<<a1<<"="<<k[i+j]<<'\n';
	  }
      }
  }

  void k0(vector<Edge> &equation, double *k, const vector<uint16_t> &noOfInitialValue)
  {
    for(uint16_t i=0; i<equation.size(); i++)
      {
	auto a1=equation[i].Calculate();
	k[i]=this->stepSize*a1;
	cout<<i<<" k0 "<<stepSize<<"*"<<a1<<"="<<k[i]<<'\n';
      }

    for(uint16_t j=this->nValue; j<this->nx; j+=this->nValue)
      {
	// cout<<"j="<<j<<"/"<<this->nx-1<<'\n';

	EquationSubstitute1(j, j+this->nValue, this->y_n, this->valuesSubstitute);

	for(uint16_t i=0; i<equation.size(); i++)
	  {
	    auto a1=equation[i].Calculate();
	    // k[i]=stepSize*equation.Calculate();
	    k[i+j]=this->stepSize*a1;
	    cout<<i+j<<" k0 "<<stepSize<<"*"<<a1<<"="<<k[i+j]<<'\n';
	  }
	// cout<<" "<<'\n';
      }
  }

  void RK4(vector<Edge> &edges, Equations &equations, const vector<uint16_t> &noOfInitialValue)
  {
    uint16_t t=stepSize;
    uint16_t n=1;
    double *k1=new double[this->nx];
    double *k2=new double[this->nx];
    double *k3=new double[this->nx];
    double *k4=new double[this->nx];

    while(n<(timeEnd-timeStart)/stepSize)
      {
	cout<<"t="<<t<<'\n';

	cout<<"-----------k1-----------"<<'\n';
	k0(edges, k1, noOfInitialValue);
	cout<<" "<<'\n';
	cout<<"-----------k2-----------"<<'\n';
	k(edges, k2, 0.5, k1);
	cout<<" "<<'\n';
	cout<<"-----------k3-----------"<<'\n';
	k(edges, k3, 0.5, k2);
	cout<<"-------------k4-----------"<<'\n';
	k(edges, k4, 1, k3);

	// for(uint16_t j=0; j<nValue; j++)
	for(uint16_t j=0; j<nx; j++)
	  {
	    newValues[j]+=(k1[j]+2*k2[j]+2*k3[j]+k4[j])/6;
	    // valuesSubstitute[j]=newValues[j];
	    cout<<newValues[j]<<'\n';
	  }

	uint16_t j=0;
	cout<<(n-1)*this->nValue<<" "<<(n)*this->nValue<<'\n';

	for(uint16_t i=(n-1)*this->nValue; i<(n)*this->nValue; i++)
	// for(uint16_t i=(n-1)*this->nx; i<(n)*this->nx; i++)
	  {
	    cout<<"i="<<i<<" "<<y_np1[i]<<" "<<y_n[j]<<" "<<newValues[j]<<" "<<j<<'\n';
	    y_np1[i]=newValues[j];
	    y_n[j]=newValues[j];
	    valuesSubstitute[j]=newValues[j];
	    j++;
	  }
	j=0;

	// break;
	cout<<"------------------------------"<<'\n';
	t+=stepSize;
	n++;
      }

	cout<<"results now"<<'\n';
	string aa;
	int a=0;
	for(uint16_t i=0; i<N; i++)
	  {
	    if(y_np1[i]!=0)
	      {
		aa+=std::to_string(y_np1[i])+";";
		a++;
	      }
	    if(a==this->nValue)
	      {
		cout<<aa<<'\n';
		aa="";
		a=0;
	      }
	  }

    delete [] k1;
    delete [] k2;
    delete [] k3;
    delete [] k4;
  }
public:
  void Calculate(const uint16_t timeStart, const uint16_t timeEnd, const uint16_t stepSize, vector<Edge> &edges, Equations &equations, const uint16_t N, const vector<uint16_t> &noOfInitialValue)
  {
    std::copy(this->y_n, this->y_n+this->nx, this->newValues);
    this->timeStart=timeStart;
    this->timeEnd=timeEnd;
    this->stepSize=stepSize;
    this->N=N;
    this->ny=(timeEnd-timeStart)/stepSize;
    RK4(edges, equations, noOfInitialValue);
  }

  RungeKutta4(){}
  RungeKutta4(const uint16_t nx, const uint16_t nv)
  {
    this->nx=nx;
    this->nValue=nv;
    // this->delta=nx/nv;

    // if(delta>nv) delta=nv;

    y_n=new double[nx];
    newValues=new double[nx];
    // valuesSubstitute=new double[delta];
    valuesSubstitute=new double[nv];
  }
  ~RungeKutta4(){}
};

#endif
