#ifndef NUMERICALMETHOD_H
#define NUMERICALMETHOD_H

class NumericalMethod
{
public:
  double *y_np1=nullptr; // results
  double *y_n=nullptr; // gets automatically substituted to the equations
  double *newValues=nullptr;
  vector<uint16_t> noOfInitialValue;
  uint16_t timeStart=0;
  uint16_t timeEnd=0;
  uint16_t stepSize=0;
  uint16_t nx=0;
  uint16_t N=0;
  uint16_t ny=0;

  NumericalMethod(){}
  virtual void Calculate(const uint16_t timeStart, const uint16_t timeEnd, const uint16_t stepSize, vector<Edge2> &edges, const vector<uint16_t> &noOfInitialValue, Equations &equations, const uint16_t N)=0;
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
  void print(const double *k)
  {
    string a;

    for(uint16_t i=0; i<nx; i++)
      {
	a+=std::to_string(k[i])+";";
      }
    cout<<a<<'\n';
  }
  void EquationSubstitute(const double constant, const double *kPrevious, const uint16_t from, const uint16_t to)
  {
    cout<<"SUBSTITUTING"<<'\n';
    print(kPrevious);
    for(uint16_t i=from; i<to; i++)
    // for(uint16_t i=0; i<nx; i++)
      {
	auto aa=y_n[i];
	// y_n[i]=y_n[i]+constant*kPrevious[i];
	y_n[i]+=constant*kPrevious[i];
	cout<<"y_n[i] "<<aa<<"+"<<constant<<"*"<<kPrevious[i]<<"="<<y_n[i]<<'\n';
      }
  }

  void EquationCalculate(Equation &equation, double *&k, const double constant, const uint16_t from, const uint16_t to)
  {
    print(k);
    for(uint16_t i=from; i<to; i++)
    // for(uint16_t i=0; i<nx; i++)
      {
	auto a1=equation.Calculate();
	// k[i]=stepSize*equation.Calculate();
	k[i]=stepSize*a1;
	cout<<"k[i] "<<stepSize<<"*"<<a1<<"="<<k[i]<<'\n';
      }
  }

  void k(Equation &equation, double *&k, const double constant, const double *kPrevious, const uint16_t from, const uint16_t to)
  {
    // Replace values in y_n
    EquationSubstitute(constant, kPrevious, from, to);
    EquationCalculate(equation, k, constant, from, to);

    // copy from newValues to y_n

    for(uint16_t i=from; i<to; i++)
    // for(uint16_t i=0; i<nx; i++)
      {
	y_n[i]=newValues[i];
	cout<<"Replace "<<y_n[i]<<" "<<newValues[i]<<'\n';
      }
  }

  void k0(Equation &equation, double *&k, const uint16_t from, const uint16_t to)
  {
    for(uint16_t i=from; i<to; i++)
    // for(uint16_t i=0; i<nx; i++)
      {
	auto a1=equation.Calculate();
	// k[i]=stepSize*equation.Calculate();
	k[i]=stepSize*a1;
	cout<<"k0 "<<stepSize<<"*"<<a1<<"="<<k[i]<<'\n';
      }
  }

  void RK4(vector<Edge2> &edges, Equations &equations)
  {
    uint16_t t=stepSize;
    uint16_t n=1;
    double *k1=new double[nx];
    double *k2=new double[nx];
    double *k3=new double[nx];
    double *k4=new double[nx];
    // double *r=new double[equations.equations.size()*nx];
    // double *d=new double[nx];
    cout<<"NY "<<ny<<" N="<<N<<'\n';

    print(y_n);
    print(y_np1);

    while(n<(timeEnd-timeStart)/stepSize)
      {
	cout<<"t="<<t<<'\n';

	// for(Equation &equation: equations.equations)
	//   {
	//     cout<<"ID "<<equation.id<<'\n';
	//     // auto equation=*e.equation;
	//     // equation=*e.equation;
	//     // cout<<"("<<e.p1.first<<" "<<e.p1.second<<"), ("
	//     // <<e.p2.first<<" "<<e.p2.second<<")"<<'\n';
	//     const uint16_t fromFrom=0;
	//     const uint16_t toFrom=nx;
	//     k0(equation, k1, fromFrom, toFrom);
	//     k(equation, k2, 0.5, k1, fromFrom, toFrom);
	//     k(equation, k3, 0.5, k2, fromFrom, toFrom);
	//     k(equation, k4, 1, k3, fromFrom, toFrom);

	//     cout<<"FROM "<<fromFrom<<" "<<toFrom<<" "<<N<<" "<<nx<<'\n';

	//     for(uint16_t i=fromFrom; i<toFrom; i++)
	//       {
	// 	// cout<<"i="<<i<<" "<<newValues[i]+(k1[i]+2*k2[i]+2*k3[i]+k4[i])/6<<'\n';
	// 	newValues[i]+=(k1[i]+2*k2[i]+2*k3[i]+k4[i])/6;
	//       }


	//     // uint16_t j=0;

	//     // for(uint16_t i=n*nx; i<(n+1)*nx; i++)
	//     // for(uint16_t i=0; i<nx; i++)
	//     //   {
	//     // 	// cout<<"i="<<i<<" "<<y_np1[i]<<" "<<y_n[j]<<" "<<newValues[j]<<'\n';
	//     // 	// y_np1[i]=newValues[j];
	//     // 	y_n[i]=newValues[i];
	//     // 	// j++;
	//     //   }

	//     // cout<<"TO"<<'\n';
	//     // for(uint16_t i=fromTo; i<toTo; i++)
	//     //   {
	//     // 	cout<<"i="<<i<<" "<<newValues[i]<<'\n';
	//     // 	// newValues[i]+=newValues[i]+stepSize*(k1[i]+2*k2[i]+2*k3[i]+k4[i])/6;
	//     //   }

	//     cout<<" "<<'\n';
	//   }

	// Equation equation;
	// for(Edge &e: edges)
	//   {
	//     // auto equation=*e.equation;
	//     equation=*e.equation;
	//     cout<<"("<<e.p1.first<<" "<<e.p1.second<<"), ("
	//     <<e.p2.first<<" "<<e.p2.second<<")"<<'\n';
	//     const uint16_t fromFrom=e.p1.first;
	//     const uint16_t toFrom=e.p1.second;
	//     k0(equation, k1, fromFrom, toFrom);
	//     k(equation, k2, 0.5, k1, fromFrom, toFrom);
	//     k(equation, k3, 0.5, k2, fromFrom, toFrom);
	//     k(equation, k4, 1, k3, fromFrom, toFrom);

	//     const uint16_t fromTo=e.p2.first;
	//     const uint16_t toTo=e.p2.second;

	//     cout<<"FROM "<<fromFrom<<" "<<toFrom<<" "<<N<<" "<<nx<<'\n';

	//     for(uint16_t i=fromFrom; i<toFrom; i++)
	//       {
	// 	// cout<<"i="<<i<<" "<<newValues[i]+(k1[i]+2*k2[i]+2*k3[i]+k4[i])/6<<'\n';
	// 	newValues[i]+=(k1[i]+2*k2[i]+2*k3[i]+k4[i])/6;
	//       }


	//     // uint16_t j=0;

	//     // for(uint16_t i=n*nx; i<(n+1)*nx; i++)
	//     // for(uint16_t i=0; i<nx; i++)
	//     //   {
	//     // 	// cout<<"i="<<i<<" "<<y_np1[i]<<" "<<y_n[j]<<" "<<newValues[j]<<'\n';
	//     // 	// y_np1[i]=newValues[j];
	//     // 	y_n[i]=newValues[i];
	//     // 	// j++;
	//     //   }

	//     // cout<<"TO"<<'\n';
	//     // for(uint16_t i=fromTo; i<toTo; i++)
	//     //   {
	//     // 	cout<<"i="<<i<<" "<<newValues[i]<<'\n';
	//     // 	// newValues[i]+=newValues[i]+stepSize*(k1[i]+2*k2[i]+2*k3[i]+k4[i])/6;
	//     //   }

	//     cout<<" "<<'\n';
	//   }
	cout<<"++++++++++++++++++++++++++++++ "<<(n)*nx<<" "<<(n+1)*nx<<" n="<<n<<'\n';
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
	    // cout<<y_np1[i]<<'\n';
	  }
	cout<<"------------------------------"<<'\n';
	t+=stepSize;
	n++;
      }

    delete [] k1;
    delete [] k2;
    delete [] k3;
    delete [] k4;
    // delete [] r;
    // delete [] d;
  }
public:
  void Calculate(const uint16_t timeStart, const uint16_t timeEnd, const uint16_t stepSize, vector<Edge2> &edges, const vector<uint16_t> &noOfInitialValue, Equations &equations, const uint16_t N)
  {
    std::copy(y_n, y_n+nx, newValues);
    this->noOfInitialValue=noOfInitialValue;
    this->timeStart=timeStart;
    this->timeEnd=timeEnd;
    this->stepSize=stepSize;
    this->N=N;
    this->ny=(timeEnd-timeStart)/stepSize;
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
    // y_n=new double[N];
    // newValues=new double[N];
  }
  ~RungeKutta4(){}
};

#endif
