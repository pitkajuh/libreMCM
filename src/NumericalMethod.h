#ifndef NUMERICALMETHOD_H
#define NUMERICALMETHOD_H

class NumericalMethod
{
public:
  double *y_np1=nullptr;
  double *y_n=nullptr;
  double *newValues=nullptr;
  uint16_t timeStart=0;
  uint16_t timeEnd=0;
  uint16_t stepSize=0;
  uint16_t nx=0;
  uint16_t N=0;
  uint16_t ny=0;

  NumericalMethod(){}
  virtual void Calculate(const uint16_t timeStart, const uint16_t timeEnd, const uint16_t stepSize, vector<Edge> &edges, Equations &equations, const uint16_t N, const vector<uint16_t> &noOfInitialValue)=0;
  virtual ~NumericalMethod()
  {
    delete [] newValues;
    delete [] y_n;
    delete [] y_np1;
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
  void EquationSubstitute(const double constant, const double *kPrevious, const uint16_t from, const uint16_t to)
  {
    // cout<<"SUBSTITUTING"<<'\n';
    // print(kPrevious);
    for(uint16_t i=from; i<to; i++)
      {
	auto aa=y_n[i];
	// y_n[i]=y_n[i]+constant*kPrevious[i];
	y_n[i]+=constant*kPrevious[i];
	// cout<<"y_n[i] "<<aa<<"+"<<constant<<"*"<<kPrevious[i]<<"="<<y_n[i]<<'\n';
      }
    cout<<"SUBSTITUTING"<<'\n';
    print(y_n, from, to);
  }

  void EquationCalculate(vector<Edge> &equation, double *&k, const double constant)
  {
    // print(k);
    // for(uint16_t i=0; i<nx; i++)
    //   {
    // 	auto a1=equation[i].Calculate();
    // 	// k[i]=stepSize*equation.Calculate();
    // 	// k[i]=kPrevious[i]+stepSize*a1;
    // 	k[i]=stepSize*a1;
    // 	cout<<"k[i] "<<stepSize<<"*"<<a1<<"="<<k[i]<<'\n';
    //   }

    for(uint16_t i=0; i<equation.size(); i++)
      {
	for(uint16_t j=0; j<nx; j++)
	  {
	    auto a1=equation[i].Calculate();
	    k[j]=stepSize*a1;
	    cout<<"k[i] "<<stepSize<<"*"<<a1<<"="<<k[i]<<'\n';
	  }
      }
  }

  void k(vector<Edge> &equation, double *&k, const double constant, double *kPrevious)
  {
    // Replace values in y_n
    EquationSubstitute(constant, kPrevious, 0, nx);
    EquationCalculate(equation, k, constant);

    // copy from newValues to y_n

    for(uint16_t i=0; i<nx; i++)
      {
	cout<<"Replace "<<y_n[i]<<" "<<newValues[i]<<'\n';
	// newValues[i]=y_n[i];
	y_n[i]=newValues[i];
	// y_n[i]=k[i];
	// cout<<"Replace "<<y_n[i]<<" "<<newValues[i]<<'\n';
      }
  }

  void k0(vector<Edge> &equation, double *&k, const vector<uint16_t> &noOfInitialValue)
  {
    cout<<"nx "<<nx<<" no of equations "<<equation.size()<<'\n';
    // uint16_t j=0;

    // for(const auto &i: noOfInitialValue)
    //   {
    // 	cout<<i<<'\n';
    //   }

    // for(uint16_t i=0; i<equation.size(); i++)
    //   {
    // 	for(uint16_t j=0; j<nx; j++)
    // 	  {
    // 	    auto a1=equation[i].Calculate();
    // 	    k[j]=stepSize*a1;
    // 	    cout<<j<<" k0 "<<stepSize<<"*"<<a1<<"="<<k[j]<<'\n';
    // 	    cout<<y_n[j]<<'\n';
    // 	    // cout<<""<<'\n';
    // 	    // break;
    // 	  }
    // 	// EquationSubstitute()
    // 	cout<<" "<<'\n';
    // 	// break;
    //   }

    for(uint16_t i=0; i<nx; i++)
      {
	auto a1=equation[i].Calculate();
	// k[i]=stepSize*equation.Calculate();
	k[i]=stepSize*a1;
	cout<<i<<" k0 "<<stepSize<<"*"<<a1<<"="<<k[i]<<'\n';
	cout<<"@@"<<'\n';
      }

    // for(uint16_t i=0; i<nx; i++)
    //   {
    // 	auto a1=equation[i].Calculate();
    // 	// k[i]=stepSize*equation.Calculate();
    // 	k[i]=stepSize*a1;
    // 	cout<<i<<" k0 "<<stepSize<<"*"<<a1<<"="<<k[i]<<'\n';
    // 	cout<<"@@"<<'\n';
    //   }
  }

  void RK4(vector<Edge> &edges, Equations &equations, const vector<uint16_t> &noOfInitialValue)
  {
    uint16_t t=stepSize;
    uint16_t n=1;
    double *k1=new double[nx];
    double *k2=new double[nx];
    double *k3=new double[nx];
    double *k4=new double[nx];

    while(n<(timeEnd-timeStart)/stepSize)
      {
	cout<<"t="<<t<<'\n';

	cout<<"-----------k0-----------"<<'\n';
	k0(edges, k1, noOfInitialValue);
	cout<<" "<<'\n';
	// cout<<"-----------k1-----------"<<'\n';
	// k(edges, k2, 0.5, k1);
	// cout<<" "<<'\n';
	// cout<<"-----------k2-----------"<<'\n';
	// k(edges, k3, 0.5, k2);
	// cout<<"-------------k3-----------"<<'\n';
	// k(edges, k4, 1, k3);
	break;
	for(uint16_t j=0; j<nx; j++)
	  {
	    newValues[j]+=(k1[j]+2*k2[j]+2*k3[j]+k4[j])/6;
	    cout<<newValues[j]<<'\n';
	  }

	uint16_t j=0;

	for(uint16_t i=n*nx; i<(n+1)*nx; i++)
	  {
	    cout<<"i="<<i<<" "<<y_np1[i]<<" "<<y_n[j]<<" "<<newValues[j]<<'\n';
	    y_np1[i]=newValues[j];
	    y_n[j]=newValues[j];
	    j++;
	  }
	j=0;

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
	    if(a==2)
	      {
		cout<<aa<<'\n';
		aa="";
		a=0;
	      }
	  }
	cout<<"------------------------------"<<'\n';
	t+=stepSize;
	n++;
      }

    delete [] k1;
    delete [] k2;
    delete [] k3;
    delete [] k4;
  }
public:
  void Calculate(const uint16_t timeStart, const uint16_t timeEnd, const uint16_t stepSize, vector<Edge> &edges, Equations &equations, const uint16_t N, const vector<uint16_t> &noOfInitialValue)
  {
    std::copy(y_n, y_n+nx, newValues);
    this->timeStart=timeStart;
    this->timeEnd=timeEnd;
    this->stepSize=stepSize;
    this->N=N;
    this->ny=(timeEnd-timeStart)/stepSize;
    RK4(edges, equations, noOfInitialValue);
  }

  RungeKutta4(){}
  RungeKutta4(const uint16_t nx)
  {
    this->nx=nx;
    y_n=new double[nx];
    newValues=new double[nx];
  }
  ~RungeKutta4(){}
};

#endif
