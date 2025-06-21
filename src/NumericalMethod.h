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
  uint16_t nx=0;
  uint16_t N=0;

  NumericalMethod(){}
  virtual void Calculate(const uint16_t timeStart, const uint16_t timeEnd, const uint16_t stepSize, const vector<Edge> &edges, const vector<uint16_t> &noOfInitialValue, Equations &equations, const uint16_t N)=0;
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

    for(uint16_t i=0; i<nx; i++)
      {
	currentValues[i]=currentValues[i]+constant*kPrevious[i];
      }

    for(uint16_t i=0; i<nx; i++)
      {
	k[i]=stepSize*equation.Calculate();
      }

    // copy from newValues to currentValues

    for(uint16_t i=0; i<nx; i++)
      {
	currentValues[i]=newValues[i];
      }
  }

  void k0(Equation &equation, double *&k)
  {
    for(uint16_t i=0; i<nx; i++)
      {
	k[i]=stepSize*equation.Calculate();
      }
  }

  void ao(const vector<Edge> &edges, const uint16_t n, double *r)
  {
    for(const Edge &e: edges)
      {
	for(uint16_t i=0; i<nx; i++)
	  {
	    cout<<newValues[i]<<" "<<currentValues[i]<<'\n';
	  }

	const uint16_t id=e.equation->id;
	uint16_t ri_from=e.from;
	uint16_t ri_to=e.from+1;
	// ri_from=nx*id;
	// ri_to=nx*(id+1);

	cout<<"r[i], from "<<ri_from<<" to "<<ri_to<<'\n';

	for(uint16_t i=ri_from; i<ri_to; i++)
	  {
	    cout<<"i="<<std::to_string(i)<<" "<<std::to_string(r[i])<<'\n';
	  }


	// SUBTRACT FROM e.from
	uint16_t from=n*nx+(e.from-1);
	uint16_t to=n*nx+e.from;

	// from=nx*(n-1);
	// to=nx*n;

	cout<<"Results subtract "<<from<<" "<<to<<'\n';

	for(uint16_t i=from; i<to; i++)
	  {
	    cout<<"SUBTRACT "<<std::to_string(i)<<'\n';
	    results[i]=results[i]-r[ri_from];
	    // results[i]=results[i]-r[ri_from];
	    // results[i]=results[(n-1)*nx+(e.from-1)]-r[ri_from];
	    ri_from++;
	  }

	// ADD TO e.to
	uint16_t results_add_from=n*nx+(e.to-1);
	uint16_t results_add_to=n*nx+e.to;

	// from=nx*(n-1);
	// to=nx*n;
	ri_from=e.from;

	cout<<"Results add "<<results_add_from<<" "<<results_add_to<<'\n';

	for(uint16_t i=results_add_from; i<results_add_to; i++)
	  {
	    cout<<"ADD "<<std::to_string(i)<<'\n';
	    results[i]=results[i]-r[ri_from];
	    // results[i]=results[(n-1)*nx+(e.to-1)]+r[ri_from];
	    ri_from++;
	  }

	uint16_t j=0;

	for(uint16_t i=nx*(n-1); i<nx*n; i++)
	  {
	    // currentValues[j]=results[i];
	    currentValues[j]=r[i];
	    newValues[j]=results[i];
	    j++;
	  }

	cout<<" "<<'\n';
      }
  }

  void RK4(const vector<Edge> &edges, Equations &equations)
  {
    uint16_t t=stepSize;
    uint16_t n=1;
    double *k1=new double[nx];
    double *k2=new double[nx];
    double *k3=new double[nx];
    double *k4=new double[nx];
    double *r=new double[equations.equations.size()*nx];
    // double *r=new double[nx];
    cout<<nx<<" "<<equations.equations.size()*nx<<" "<<std::to_string((timeEnd-timeStart)/stepSize)<<'\n';
    // while(t<=timeEnd)
    while(n<(timeEnd-timeStart)/stepSize)
      {
	cout<<"t="<<t<<'\n';

	for(Equation &equation: equations.equations)
	  {
	    k0(equation, k1);
	    k(equation, k2, 0.5, k1);
	    k(equation, k3, 0.5, k2);
	    k(equation, k4, 1, k3);
	    string aa;

	    uint16_t j=0;

	    for(uint16_t i=equation.id*nx; i<(equation.id+1)*nx; i++)
	      {
		r[i]=currentValues[j]+stepSize*(k1[j]+2*k2[j]+2*k3[j]+k4[j])/6;
		// currentValues[i]=r[i]; // Set later
		aa+=std::to_string(r[i]);
		aa+=";";
		j++;
	      }
	    j=0;
	    cout<<aa<<'\n';
	  }
	ao(edges, n, r);
	cout<<"------------------------------"<<'\n';
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
  void Calculate(const uint16_t timeStart, const uint16_t timeEnd, const uint16_t stepSize, const vector<Edge> &edges, const vector<uint16_t> &noOfInitialValue, Equations &equations, const uint16_t N)
  {
    std::copy(currentValues, currentValues+nx, newValues);
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
    currentValues=new double[nx];
    newValues=new double[nx];
  }
  ~RungeKutta4(){}
};

#endif
