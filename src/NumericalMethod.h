#ifndef NUMERICALMETHOD_H
#define NUMERICALMETHOD_H

#include "Graph.h"

class NumericalMethod
{
public:
  vector<double> y_np1; // y_{n+1}
  vector<double> y_n; // y_{n}
  vector<double> valuesSubstitute;
  vector<double> newValues;
  uint16_t nx=0;
  uint16_t N=0;
  uint16_t ny=0;
  uint16_t nValue=0;

  NumericalMethod(){}
  virtual void Calculate(FileSettings &simulationParameters, Graph &graph, const uint16_t N, const vector<uint16_t> &noOfInitialValue, const string &directory)=0;
  virtual ~NumericalMethod()
  {
    // delete [] newValues;
    // delete [] valuesSubstitute;
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

  void Calculate(vector<Edge> &equation, vector<double> &k, const uint16_t stepSize)
  {
    const uint16_t size=equation.size();

#pragma omp parallel for
    for(uint16_t i=0; i<size; i++)
      {
	auto a1=equation[i].Calculate();
	k[i]=stepSize*a1;
      }
  }

  void Calculate1(vector<Edge> &equation, vector<double> &k, const uint16_t j, const uint16_t stepSize)
  {
    for(uint16_t i=0; i<equation.size(); i++)
      {
	auto a1=equation[i].Calculate();
	k[i+j]=stepSize*a1;
      }
  }

  void EquationSubstitute1(const uint16_t from, const uint16_t to, const vector<double> &kFrom, vector<double> &kTo)
  {
#pragma omp parallel for
    for(uint16_t i=from; i<to; i++)
      {
	kTo[i-from]=kFrom[i];
      }
  }

  void EquationSubstitute(const uint16_t from, const uint16_t to, const vector<double> &kFrom, vector<double> &kTo)
  {
    for(uint16_t i=from; i<to; i++)
      {
	kTo[i-from]=kFrom[i];
      }

  }

  void k(vector<Edge> &equation, vector<double> &k, const double constant, vector<double> &kPrevious, const uint16_t stepSize)
  {
#pragma omp parallel for
    for(uint16_t i=0; i<this->nx; i+=this->nValue)
      {
	for(uint16_t j=i; j<i+this->nValue; j++)
	  {
	    const double a=this->y_n[j]+constant*kPrevious[j];
	    this->valuesSubstitute[j-i]=a;
	  }
	Calculate1(equation, k, i, stepSize);
      }
  }

  void k0(vector<Edge> &equation, vector<double> &k, vector<double> &k1, const uint16_t stepSize)
  {
    Calculate(equation, k, stepSize);

#pragma omp parallel for
    for(uint16_t i=this->nValue; i<this->nx; i+=this->nValue)
      {
	EquationSubstitute(i, i+this->nValue, k1, this->valuesSubstitute);
	Calculate1(equation, k, i, stepSize);
      }
  }

  void RK4(vector<Edge> &edges, const uint16_t stepSize)
  {
    vector<double> k1(this->nx);
    vector<double> k2(this->nx);
    vector<double> k3(this->nx);
    vector<double> k4(this->nx);

// #pragma omp parallel for
    for(uint16_t n=this->nValue; n<ny+1; n++)
      {
	k0(edges, k1, this->y_n, stepSize);
	k(edges, k2, 0.5, k1, stepSize);
	k(edges, k3, 0.5, k2, stepSize);
	k(edges, k4, 1, k3, stepSize);
#pragma omp parallel for
	for(uint16_t i=0; i<this->nx; i++)
	  {
	    double aa=(k1[i]+2*k2[i]+2*k3[i]+k4[i])/6;
	    this->newValues[i]+=aa;
	  }
	uint16_t j=0;
// #pragma omp parallel for
	for(uint16_t i=(n-1)*this->nx; i<n*this->nx; i++)
	  {
	    this->y_np1[i]=this->newValues[j];
	    this->y_n[j]=this->newValues[j];
	    j++;
	  }
	EquationSubstitute1(0, this->nValue, this->newValues, this->valuesSubstitute);
      }
  }
public:
  void WriteResultsSubSub(std::ofstream &file1, const uint16_t vertex, const uint16_t ivt)
  {
    uint16_t k=1;

    for(uint16_t i=vertex; i<this->N; i+=this->nValue)
      {
	if(k==ivt+1)
	  {
	    file1<<'\n';
	    k=1;
	  }
	file1<<y_np1[i];
	if(k<ivt) file1<<";";

	k++;
      }
  }

  void WriteResultsSub(const uint16_t vertex, const uint16_t initialValues, const string &directory)
  {
    std::ofstream file1(directory+std::to_string(vertex)+".txt");

    for(uint16_t i=0; i<initialValues; i++)
      {
	WriteResultsSubSub(file1, vertex, initialValues);
      }
    file1.close();
  }

  void WriteResults(const vector<uint16_t> &noOfInitialValue, const string &directory)
  {
#pragma omp parallel for
    for(uint16_t i=0; i<this->nValue; i++)
      {
	WriteResultsSub(i, noOfInitialValue[i], directory);
      }
  }

  void Calculate(FileSettings &simulationParameters, Graph &graph, const uint16_t N1, const vector<uint16_t> &noOfInitialValue, const string &directory)
  {
    std::copy(this->y_n.begin(), this->y_n.begin()+this->nx, this->newValues.begin());
    this->N=N1;
    this->ny=(simulationParameters.GetTimeEnd()-simulationParameters.GetTimeStart())/simulationParameters.GetStepSize();
    RK4(graph.GetEdges(), simulationParameters.GetStepSize());
    WriteResults(noOfInitialValue, directory);
  }

  void Create(const uint16_t nx1, const uint16_t nv)
  {
    this->nx=nx1;
    this->nValue=nv;
    this->y_n.reserve(nx1);
    this->newValues.reserve(nx1);
    this->valuesSubstitute.reserve(nv);
  }

  RungeKutta4(){}
  ~RungeKutta4(){}
};

#endif
