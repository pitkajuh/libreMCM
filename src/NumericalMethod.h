#ifndef NUMERICALMETHOD_H
#define NUMERICALMETHOD_H

class NumericalMethod
{
public:
  double *y_np1=nullptr;
  double *y_n=nullptr;
  double *newValues=nullptr;
  vector<uint16_t> noOfInitialValue;
  uint16_t timeStart=0;
  uint16_t timeEnd=0;
  uint16_t stepSize=0;
  uint16_t nx=0;
  uint16_t N=0;

  NumericalMethod(){}
  virtual void Calculate(const uint16_t timeStart, const uint16_t timeEnd, const uint16_t stepSize, vector<Edge> &edges, const vector<uint16_t> &noOfInitialValue, Equations &equations, const uint16_t N)=0;
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
  void k(Equation &equation, double *&k, const double constant, const double *kPrevious, const uint16_t from, const uint16_t to)
  {
    // Replace values in y_n

    // for(uint16_t i=0; i<nx; i++)
    for(uint16_t i=from; i<=to; i+=nx)
      {
	y_n[i]=y_n[i]+constant*kPrevious[i];
	// cout<<y_n[i]<<'\n';
      }
    // cout<<" "<<'\n';
    // for(uint16_t i=0; i<nx; i++)
    for(uint16_t i=from; i<=to; i+=nx)
      {
	k[i]=stepSize*equation.Calculate();
      }

    // copy from newValues to y_n

    // for(uint16_t i=0; i<nx; i++)
    for(uint16_t i=from; i<=to; i+=nx)
      {
	y_n[i]=newValues[i];
	// cout<<y_n[i]<<'\n';
      }
    // cout<<" "<<'\n';
  }

  void k0(Equation &equation, double *&k, const uint16_t from, const uint16_t to)
  {
    // for(uint16_t i=0; i<nx; i++)
    for(uint16_t i=from; i<=to; i+=nx)
      {
	k[i]=stepSize*equation.Calculate();
      }
  }

  void RK4(vector<Edge> &edges, Equations &equations)
  {
    uint16_t t=stepSize;
    uint16_t n=1;
    double *k1=new double[nx];
    double *k2=new double[nx];
    double *k3=new double[nx];
    double *k4=new double[nx];
    double *r=new double[equations.equations.size()*nx];
    double *d=new double[nx];

    for(uint16_t i=0; i<nx; i++)
      {
	cout<<std::to_string(i)<<" "<<y_n[i]<<'\n';
      }

    while(n<(timeEnd-timeStart)/stepSize)
      {
	cout<<"t="<<t<<'\n';

	// for(Equation &equation: equations.equations)
	for(Edge &e: edges)
	  {
	    auto equation=*e.equation;
	    auto id=equation.id;

	    cout<<"("<<e.p1.first<<" "<<e.p1.second<<"), ("<<e.p2.first<<" "<<e.p2.second<<")"<<'\n';

	    // k0(equation, k1, from, to);
	    // k(equation, k2, 0.5, k1, from, to);
	    // k(equation, k3, 0.5, k2, from, to);
	    // k(equation, k4, 1, k3, from, to);

	    // for(uint16_t i=)
	    //   {
	    // 	// r[i]=newValues[j]+stepSize*(k1[j]+2*k2[j]+2*k3[j]+k4[j])/6;
	    //   }

	    cout<<" "<<'\n';
	  }
	cout<<"++++++++++++++++++++++++++++++"<<'\n';

	cout<<"------------------------------"<<'\n';
	t+=stepSize;
	n++;
      }

    delete [] k1;
    delete [] k2;
    delete [] k3;
    delete [] k4;
    delete [] r;
    delete [] d;
  }
public:
  void Calculate(const uint16_t timeStart, const uint16_t timeEnd, const uint16_t stepSize, vector<Edge> &edges, const vector<uint16_t> &noOfInitialValue, Equations &equations, const uint16_t N)
  {
    std::copy(y_n, y_n+nx, newValues);
    this->noOfInitialValue=noOfInitialValue;
    this->timeStart=timeStart;
    this->timeEnd=timeEnd;
    this->stepSize=stepSize;
    this->N=N;
    RK4(edges, equations);

    // for(const Edge &e: edges)
    //   {
    // 	cout<<"From "<<e.from<<" To "<<e.to<<'\n';
    // 	RK4(e.from, e.to, e.equation);
    // 	break;
    //   }
  }

  RungeKutta4(){}
  RungeKutta4(const uint16_t nx)
  {
    this->nx=nx;
    cout<<"nx "<<nx<<'\n';
    y_n=new double[nx];
    newValues=new double[nx];
  }
  ~RungeKutta4(){}
};

#endif
