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
  virtual void Calculate(const uint16_t timeStart, const uint16_t timeEnd, const uint16_t stepSize, vector<Edge> &edges, const uint16_t N, const vector<uint16_t> &noOfInitialValue)=0;
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
	cout<<i<<" k0 "<<stepSize<<"*"<<a1<<"="<<k[i]<<'\n';
	cout<<" "<<'\n';
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
	cout<<i+j<<" k01 "<<stepSize<<"*"<<a1<<"="<<k[i+j]<<'\n';
	cout<<" "<<'\n';

      }
  }

  void EquationSubstitute1(const uint16_t from, const uint16_t to, const double *kFrom, double *kTo)
  {
    for(uint16_t i=from; i<to; i++)
      {
	cout<<"i2="<<i<<" "<<kFrom[i]<<'\n';
	kTo[i-from]=kFrom[i];
      }
    // cout<<" "<<'\n';
  }

  void EquationSubstitute(const uint16_t from, const uint16_t to, const double *kFrom, double *kTo)
  {
    for(uint16_t i=from; i<to; i++)
      {
	cout<<"i2="<<i<<" "<<kFrom[i]<<'\n';
	kTo[i-from]=kFrom[i];
      }

  }

  // void k(vector<Edge> &equation, double *k, const double constant, double *kPrevious, const uint16_t stepSize)
  // {
  //   for(uint16_t i=0; i<this->nx; i++)
  //     {
  // 	// cout<<"subs "<<valuesSubstitute[i]<<"+"<<constant<<"*"<<kPrevious[i]<<"="<<valuesSubstitute[i]+constant*kPrevious[i]<<'\n';
  // 	// const double a=valuesSubstitute[i]+constant*kPrevious[i];
  // 	kPrevious[i]=this->y_n[i]+constant*kPrevious[i];
  // 	// const double a=this->y_n[i]+constant*kPrevious[i];
  // 	// y_n[i]+=constant*kPrevious[i];
  // 	// const double a=this->y_np1[i]+constant*kPrevious[i];
  // 	// this->valuesSubstitute[i]=a;
  // 	// this->valuesSubstitute[i-this->nValue]=a;

  // 	// valuesSubstitute[i]=+constant*kPrevious[i];
  // 	// cout<<"now "<<valuesSubstitute[i]<<'\n';
  //     }
  //   EquationSubstitute(this->nValue, this->nx, kPrevious, this->valuesSubstitute);
  //   k0(equation, k, kPrevious, stepSize);
  // }

  void k(vector<Edge> &equation, double *k, const double constant, double *kPrevious, const uint16_t stepSize)
  {
    for(uint16_t i=0; i<this->nValue; i++)
    // for(uint16_t i=this->nValue; i<this->nx; i++)
    // for(uint16_t i=0; i<this->nx; i++)
      {
	// cout<<"subs "<<valuesSubstitute[i]<<"+"<<constant<<"*"<<kPrevious[i]<<"="<<valuesSubstitute[i]+constant*kPrevious[i]<<'\n';
	// const double a=valuesSubstitute[i]+constant*kPrevious[i];

	const double a=this->y_n[i]+constant*kPrevious[i];
	cout<<i<<" "<<this->y_n[i]<<"+"<<constant<<"*"<<kPrevious[i]<<"="<<a<<'\n';
	// y_n[i]+=constant*kPrevious[i];
	// const double a=this->y_np1[i]+constant*kPrevious[i];
	this->valuesSubstitute[i]=a;
	// this->valuesSubstitute[i-this->nValue]=a;

	// valuesSubstitute[i]=+constant*kPrevious[i];
	// cout<<"now "<<valuesSubstitute[i]<<'\n';
      }
    // EquationSubstitute(0, this->nValue, this->y_n, this->valuesSubstitute);
    k0(equation, k, kPrevious, stepSize);
  }

  void k0(vector<Edge> &equation, double *k, double *k1, const uint16_t stepSize)
  {
    Calculate(equation, k, stepSize);

    for(uint16_t i=this->nValue; i<this->nx; i+=this->nValue)
    // for(uint16_t i=0; i<this->nx; i+=this->nValue) // wrong
    // for(uint16_t i=this->nValue-1; i<this->nx; i+=this->nValue) // crash
      {
	// cout<<"ii="<<i<<"/"<<this->nx-1<<'\n';
	cout<<i<<" "<<i+this->nValue<<'\n';
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

	cout<<"-----------k1-----------"<<'\n';
	k0(edges, k1, this->y_n, stepSize);
	cout<<"-----------k2-----------"<<'\n';
	k(edges, k2, 0.5, k1, stepSize);
	cout<<"-----------k3-----------"<<'\n';
	k(edges, k3, 0.5, k2, stepSize);
	cout<<"-------------k4-----------"<<'\n';
	k(edges, k4, 1, k3, stepSize);
	// break;
	for(uint16_t i=0; i<this->nx; i++)
	  {
	    double aa=(k1[i]+2*k2[i]+2*k3[i]+k4[i])/6;
	    this->newValues[i]+=aa;
	    cout<<aa<<" "<<k1[i]<<" "<<k2[i]<<" "<<k3[i]<<" "<<k4[i]<<"="<<newValues[i]<<'\n';
	    // cout<<"+("<<k1[i]<<"+"<<"2*"<<k2[i]<<"+2*"<<k3[i]<<"+"<<k4[i]<<")/6"<<"="<<newValues[i]<<'\n';
	  }
	print(newValues, 0, nx);
	uint16_t j=0;

	for(uint16_t i=(n-1)*this->nx; i<n*this->nx; i++)
	  {
	    // cout<<i<<" "<<n*this->nx<<" value before is "<<y_np1[i]<<'\n';
	    this->y_np1[i]=this->newValues[j];
	    this->y_n[j]=this->newValues[j];
	    j++;
	  }
	j=0;
	EquationSubstitute1(0, this->nValue, this->newValues, this->valuesSubstitute);
	// EquationSubstitute1(this->nValue, this->nx, this->newValues, this->valuesSubstitute);
	break;
	t+=stepSize;
	n++;
      }
    delete [] k1;
    delete [] k2;
    delete [] k3;
    delete [] k4;
  }
public:
  void WriteResultsSubSub(std::ofstream &file1, const uint16_t vertex, const uint16_t iv, const uint16_t ivt)
  {
    uint16_t i=iv;
    uint16_t k=1;
    cout<<this->N<<" "<<ivt<<" "<<iv<<'\n';
    // while(i<this->N/ivt)
    while(i<this->N)
      {
	// if(k==ivt+1)
	//   {
	//     file1<<'\n';
	//     k=1;
	//   }
	// file1<<y_np1[i];
	// if(k<ivt) file1<<";";


	file1<<y_np1[i];
	file1<<'\n';



	// i+=this->nValue;

	i+=this->nx;
	// i++;
	k++;
      }
  }

  void WriteResultsSub(const uint16_t vertex, const uint16_t initialValues)
  {
    std::ofstream file1(std::to_string(vertex)+".txt");

    for(uint16_t i=0; i<initialValues; i++)
      {
	// WriteResultsSubSub(file1, vertex, i, initialValues);
	WriteResultsSubSub(file1, vertex, i*this->nValue, initialValues);
	// break;
      }
    file1.close();
  }

  void WriteResults(const vector<uint16_t> &noOfInitialValue)
  {
    // for(uint16_t i=0; i<N; i++)
    //   {
    // 	cout<<y_np1[i]<<'\n';
    //   }
    for(uint16_t i=0; i<this->nValue; i++)
      {
	WriteResultsSub(i, noOfInitialValue[i]);
	break;
      }
  }

  void Calculate(const uint16_t timeStart, const uint16_t timeEnd, const uint16_t stepSize, vector<Edge> &edges, const uint16_t N, const vector<uint16_t> &noOfInitialValue)
  {
    std::copy(this->y_n, this->y_n+this->nx, this->newValues);
    this->N=N;
    this->ny=(timeEnd-timeStart)/stepSize;
    RK4(edges, stepSize);
    WriteResults(noOfInitialValue);
  }

  RungeKutta4(){}
  RungeKutta4(const uint16_t nx, const uint16_t nv)
  {
    this->nx=nx;
    this->nValue=nv;
    y_n=new double[nx];
    newValues=new double[nx];
    valuesSubstitute=new double[nv];
  }
  ~RungeKutta4(){}
};

#endif
