#ifndef NUMERICALMETHOD_H
#define NUMERICALMETHOD_H

class NumericalMethod
{
public:
  double *y_np1=nullptr;
  double *y_n=nullptr;
  double *newValues=nullptr;
  double *valuesSubstitute=nullptr;
  uint16_t nx=0;
  uint16_t N=0;
  uint16_t ny=0;
  uint16_t nValue=0;

  NumericalMethod(){}
  virtual void Calculate(const uint16_t timeStart, const uint16_t timeEnd, const uint16_t stepSize, vector<Edge> &edges, const uint16_t N)=0;
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

  void Calculate(vector<Edge> &equation, double *k, const uint16_t stepSize)
  {
    for(uint16_t i=0; i<equation.size(); i++)
      {
	auto a1=equation[i].Calculate();
	k[i]=stepSize*a1;
	// cout<<i<<" k0 "<<stepSize<<"*"<<a1<<"="<<k[i]<<'\n';
      }
  }

  void Calculate1(vector<Edge> &equation, double *k, const uint16_t j, const uint16_t stepSize)
  {
    for(uint16_t i=0; i<equation.size(); i++)
    // for(uint16_t i=0; i<equation.size(); i+=1+j)
      {
	auto a1=equation[i].Calculate();
	k[i+j]=stepSize*a1;
	// k[i]=stepSize*a1;
	// cout<<i<<" k0 "<<stepSize<<"*"<<a1<<"="<<k[i]<<'\n';
      }
  }

  void EquationSubstitute(const uint16_t from, const uint16_t to, const double *kFrom, double *kTo)
  {
    for(uint16_t i=from; i<to; i++)
      {
	// cout<<"i="<<i<<" "<<kFrom[i]<<'\n';
	kTo[i-from]=kFrom[i];
      }
  }

  void k(vector<Edge> &equation, double *k, const double constant, double *kPrevious, const uint16_t stepSize)
  {
    for(uint16_t i=0; i<this->nValue; i++)
      {
	// cout<<"subs "<<valuesSubstitute[i]<<"+"<<constant<<"*"<<kPrevious[i]<<"="<<valuesSubstitute[i]+constant*kPrevious[i]<<'\n';
	// const double a=valuesSubstitute[i]+constant*kPrevious[i];
	const double a=this->y_n[i]+constant*kPrevious[i];
	this->valuesSubstitute[i]=a;
	// valuesSubstitute[i]=+constant*kPrevious[i];
	// cout<<"now "<<valuesSubstitute[i]<<'\n';
      }
    k0(equation, k, kPrevious, stepSize);
  }

  void k0(vector<Edge> &equation, double *k, double *k1, const uint16_t stepSize)
  {
    Calculate(equation, k, stepSize);

    for(uint16_t i=this->nValue; i<this->nx; i+=this->nValue)
      {
	// cout<<"i="<<i<<"/"<<this->nx-1<<'\n';
	EquationSubstitute(i, i+this->nValue, k1, this->valuesSubstitute);
	Calculate1(equation, k, i, stepSize);
      }
  }

  void RK4(vector<Edge> &edges, const uint16_t stepSize)
  {
    double t=stepSize;
    uint16_t n=2;
    n=this->nValue;
    double *k1=new double[this->nx];
    double *k2=new double[this->nx];
    double *k3=new double[this->nx];
    double *k4=new double[this->nx];
    // double *k1=new double[this->nValue];
    // double *k2=new double[this->nValue];
    // double *k3=new double[this->nValue];
    // double *k4=new double[this->nValue];

    while(n<ny+1)
      {
	// cout<<"t="<<t<<'\n';

	// cout<<"-----------k1-----------"<<'\n';
	k0(edges, k1, this->y_n, stepSize);
	// cout<<" "<<'\n';
	// cout<<"-----------k2-----------"<<'\n';
	k(edges, k2, 0.5, k1, stepSize);
	// cout<<" "<<'\n';
	// cout<<"-----------k3-----------"<<'\n';
	k(edges, k3, 0.5, k2, stepSize);
	// cout<<"-------------k4-----------"<<'\n';
	k(edges, k4, 1, k3, stepSize);

	// for(uint16_t i=0; i<nValue; i++)
	for(uint16_t i=0; i<this->nx; i++)
	  {
	    this->newValues[i]+=(k1[i]+2*k2[i]+2*k3[i]+k4[i])/6;
	    // valuesSubstitute[i]=this->newValues[i];
	    // cout<<"result "<<this->newValues[i]<<'\n';
	  }

	uint16_t j=0;

	// for(uint16_t i=(n-1)*this->nValue; i<n*this->nValue; i++)

	// for(uint16_t i=0; i<nx; i++)
	//   {
	//     cout<<"i "<<i<<" "<<this->newValues[i]<<'\n';
	//   }

	for(uint16_t i=(n-1)*this->nx; i<n*this->nx; i++)
	  {
	    // cout<<"i="<<i<<" "<<y_np1[i]<<" "<<y_n[j]<<" "<<this->newValues[j]<<" "<<j<<" "<<i<<'\n';
	    // cout<<"i "<<j<<" "<<this->newValues[j]<<'\n';
	    // cout<<"i "<<i<<" "<<n*this->nValue<<'\n';
	    // cout<<i<<" "<<this->newValues[j]<<'\n';
	    this->y_np1[i]=this->newValues[j];
	    this->y_n[j]=this->newValues[j];
	    // valuesSubstitute[j]=newValues[j];
	    j++;
	  }
	j=0;
	// for(uint16_t i=(n-this->nValue)*this->nx+this->nValue; i<(n-1)*this->nx; i++)
	// for(uint16_t i=(n-this->nValue)*this->nx; i<(n-this->nValue)*this->nx+this->nValue; i++)
	//   {
	//     // valuesSubstitute[i]=newValues[];
	//     cout<<i<<" "<<i+nx<<'\n';
	//   }
	// EquationSubstitute((n-this->nValue)*this->nx, (n-this->nValue)*this->nx+this->nValue, this->newValues, this->valuesSubstitute);
	EquationSubstitute(0, this->nValue, this->newValues, this->valuesSubstitute);
	// for(uint16_t i=)

	// break;
	// cout<<" "<<'\n';


	// break;
	// cout<<"------------------------------"<<'\n';
	t+=stepSize;
	n++;
      }

	// cout<<"results now"<<'\n';
	// string aa;
	// int a=0;
	// for(uint16_t i=0; i<N; i++)
	//   {
	//     if(y_np1[i]!=0)
	//       {
	// 	aa+=std::to_string(y_np1[i])+";";
	// 	a++;
	//       }
	//     if(a==this->nValue)
	//       {
	// 	cout<<aa<<'\n';
	// 	aa="";
	// 	a=0;
	//       }
	//   }

	delete [] k1;
	delete [] k2;
	delete [] k3;
	delete [] k4;
  }
public:
  void WriteResults1(const uint16_t vertex)
  {
    string aa="";
    uint16_t to=0;
    uint16_t i=vertex;
    uint16_t j=0;
    uint16_t k=1;
    std::ofstream file1(std::to_string(vertex)+".txt");

    while(i<this->N)
      {
	if(k==this->nValue)
	  {
	    file1<<'\n';
	    k=1;
	  }
	// cout<<y_np1[i]<<" "<<y_np1[i+nx]<<'\n';
	file1<<y_np1[i];
	i+=this->nValue;
	// i+=this->nx;
	k++;
      }
    file1.close();
  }

  void WriteResults()
  {
    for(uint16_t i=0; i<this->nValue; i++)
      {
	WriteResults1(i);
	// break;
      }
  }

  void Calculate(const uint16_t timeStart, const uint16_t timeEnd, const uint16_t stepSize, vector<Edge> &edges, const uint16_t N)
  {
    std::copy(this->y_n, this->y_n+this->nx, this->newValues);
    cout<<y_n[0]<<" "<<y_n[1]<<'\n';
    this->N=N;
    this->ny=(timeEnd-timeStart)/stepSize;
    RK4(edges, stepSize);
    // for(uint16_t i=0; i<N; i++)
    //   {
    // 	cout<<y_np1[i]<<'\n';
    //   }
    WriteResults();
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
    // newValues=new double[nv];
    // valuesSubstitute=new double[delta];
    valuesSubstitute=new double[nv];
  }
  ~RungeKutta4(){}
};

#endif
