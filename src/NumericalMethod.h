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
    while(n<=(timeEnd-timeStart)/stepSize)
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
		// cout<<equation.id<<" "<<i<<"/"<<(equation.id+1)*nx-1<<" "<<nx-1<<" "<<(equation.id+1)*nx-equation.id*nx-1<<'\n';


		r[i]=currentValues[j]+stepSize*(k1[j]+2*k2[j]+2*k3[j]+k4[j])/6;
		// currentValues[i]=r[i]; // Set later
		aa+=std::to_string(r[i]);
		aa+=";";
		j++;
	      }
	    j=0;
	    // cout<<aa<<'\n';
	  }

	for(const Edge &e: edges)
	  {
	    // for(const auto &i: noOfInitialValue)
	    //   {
	    // 	cout<<i<<'\n';
	    //   }

	    // cout<<e.from<<" "<<e.to<<'\n';
	    const uint16_t id=e.equation->id;

	    cout<<"r[i], from "<<nx*id<<" to "<<nx*(id+1)<<'\n';

	    // cout<<"results "<<e.from*nx*n<<" to "<<e.from*(nx*n+1)-1<<" N="<<N<<'\n';
	    // cout<<"results "<<(e.from)*nx<<" "<<(e.from)*(nx+1)-1<<" "<<N<<" "<<n<<" "<<n*nx<<'\n';
	    // cout<<"results "<<n<<" "<<(n-1)*nx<<" "<<n*nx<<'\n';



	    // cout<<"results "<<id<<" from "<<(n)*(nx)+(e.from-1)<<" to "<<n*(nx)+e.from<<" r.size "<<equations.equations.size()*nx<<'\n';
	    cout<<"results "<<id<<" from "<<(n-1)*(nx)<<" to "<<n*(nx)<<" r.size "<<equations.equations.size()*nx<<'\n';



	    for(uint16_t i=0; i<nx; i++)
	      {
		for(uint16_t j=0; j<n; j++)
		  {

		  }
	      }

	    // SUBTRACT FROM e.from

	    for(uint16_t i=nx*id; i<(id+1)*nx; i++)
	      {

	      }

	    // ADD TO e.to


	  }
	cout<<" "<<'\n';
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
