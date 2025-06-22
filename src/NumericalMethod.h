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

  void UpdateValues(double *r, const uint16_t n)
  {
    uint16_t j=0;
    string a;
    for(uint16_t i=nx*(n-1); i<nx*n; i++)
      {
	// y_n[j]=y_np1[i];
	// y_n[j]=r[i];
	newValues[j]=y_np1[i];
	y_n[j]=y_np1[i];
	a+=std::to_string(y_np1[i])+";";
	j++;
      }
    cout<<nx*(n-1)<<" "<<nx*n<<'\n';
    cout<<a<<'\n';
  }

  void ao(const vector<Edge> &edges, const uint16_t n, double *r)
  {
    for(const Edge &e: edges)
      {
	// for(uint16_t i=0; i<nx; i++)
	//   {
	//     cout<<newValues[i]<<" "<<y_n[i]<<'\n';
	//   }

	// const uint16_t id=e.equation->id;
	// uint16_t ri_from=e.from;
	// uint16_t ri_to=e.from+1;
	// ri_from=nx*id;
	// ri_to=nx*(id+1);

	// cout<<"Equation "<<id<<" r[i], from "<<ri_from<<" to "<<ri_to<<'\n';

	// for(uint16_t i=ri_from; i<ri_to; i++)
	//   {
	//     cout<<"i="<<std::to_string(i)<<" "<<std::to_string(r[i])<<'\n';
	//   }


	// // SUBTRACT FROM e.from
	// uint16_t from=n*nx+(e.from-1);
	// uint16_t to=n*nx+e.from;

	// // from=nx*(n-1);
	// // to=nx*n;

	// cout<<"Y_Np1 subtract "<<from<<" "<<to<<'\n';

	// for(uint16_t i=from; i<to; i++)
	//   {
	//     cout<<"SUBTRACT "<<std::to_string(i)<<" "<<y_np1[i]<<'\n';
	//     y_np1[i]=y_np1[i]-r[ri_from];
	//     // y_np1[i]=y_np1[i]-r[ri_from];
	//     // y_np1[i]=y_np1[(n-1)*nx+(e.from-1)]-r[ri_from];
	//     ri_from++;
	//   }

	// // ADD TO e.to
	// uint16_t y_np1_add_from=n*nx+(e.to-1);
	// uint16_t y_np1_add_to=n*nx+e.to;

	// // from=nx*(n-1);
	// // to=nx*n;
	// ri_from=e.from;

	// cout<<"y_np1 add "<<y_np1_add_from<<" "<<y_np1_add_to<<'\n';

	// for(uint16_t i=y_np1_add_from; i<y_np1_add_to; i++)
	//   {
	//     cout<<"ADD "<<std::to_string(i)<<'\n';
	//     y_np1[i]=y_np1[i]-r[ri_from];
	//     // y_np1[i]=y_np1[(n-1)*nx+(e.to-1)]+r[ri_from];
	//     ri_from++;
	//   }

	// UpdateValues(r, n);

	cout<<" "<<'\n';
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
    // double *r=new double[nx];
    // cout<<nx<<" "<<equations.equations.size()*nx<<" "<<std::to_string((timeEnd-timeStart)/stepSize)<<" N="<<N<<'\n';
    // while(t<=timeEnd)
    // while(n<(timeEnd-timeStart)/stepSize)
    //   {
    // 	cout<<"t="<<t<<'\n';

    // 	for(Equation &equation: equations.equations)
    // 	  {
    // 	    k0(equation, k1);
    // 	    k(equation, k2, 0.5, k1);
    // 	    k(equation, k3, 0.5, k2);
    // 	    k(equation, k4, 1, k3);

    // 	    // string aa;

    // 	    uint16_t j=0;

    // 	    for(uint16_t i=equation.id*nx; i<(equation.id+1)*nx; i++)
    // 	      {
    // 		r[i]=y_n[j]+stepSize*(k1[j]+2*k2[j]+2*k3[j]+k4[j])/6;
    // 		// r[i]=newValues[j]+stepSize*(k1[j]+2*k2[j]+2*k3[j]+k4[j])/6;
    // 		cout<<i<<" "<<r[i]<<'\n';
    // 		// y_n[i]=r[i]; // Set later
    // 		// aa+=std::to_string(r[i]);
    // 		// aa+=";";
    // 		j++;
    // 	      }
    // 	    j=0;
    // 	    // cout<<aa<<'\n';
    // 	  }
    // 	cout<<"++++++++++++++++++++++++++++++"<<'\n';
    // 	ao(edges, n, r);
    // 	cout<<"------------------------------"<<'\n';
    // 	t+=stepSize;
    // 	n++;
    //   }

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
	    // cout<<"ID "<<id<<" from "<<e.from<<" to "<<e.to<<", "<<nx<<" "<<edges.size()<<" n="<<n<<'\n';

	    // uint16_t from;
	    // uint16_t to;

	    // from=e.from*id;
	    // to=e.from*(id+1);
	    // cout<<from<<" "<<to<<'\n';
	    // from=e.from*nx;
	    // to=e.from*(nx+1);
	    // cout<<from<<" "<<to<<'\n';
	    // from=e.from*n;
	    // to=e.from*(n+1);
	    // cout<<from<<" "<<to<<'\n';
	    // from=e.from*nx;
	    // to=e.from*(nx+1);
	    // cout<<from<<" "<<to<<'\n';
	    // from=e.from*nx*n;
	    // to=e.from*(nx*n+1);
	    // cout<<from<<" "<<to<<'\n';
	    // from=nx*id;
	    // to=nx*(id+1);
	    // cout<<from<<" "<<to<<'\n';
	    // from=nx*id*n;
	    // to=nx*(id*n+1);

	    // from=nx*id;
	    // to=nx*(id+1);
	    // cout<<from<<" "<<to<<'\n';

	    // for(uint16_t i=from; i<to; i+=(N/nx)/2)
	    //   {
	    // 	cout<<"i="<<std::to_string(i)<<'\n';
	    //   }

	    // from=e.from;
	    // to=e.from+noOfInitialValue[e.from];
	    // to=e.from+noOfInitialValue[e.to];
	    // // to=e.to+noOfInitialValue[e.to];
	    // cout<<"Move from "<<from<<" "<<to-1<<'\n';

	    // for(uint16_t i=from; i<to; i++)
	    //   {
	    // 	cout<<i<<'\n';
	    //   }


	    // from=e.to;
	    // to=e.to+noOfInitialValue[e.to];
	    // cout<<"Move to "<<from<<" "<<to-1<<'\n';
	    // for(uint16_t i=from; i<to; i++)
	    //   {
	    // 	cout<<i<<'\n';
	    //   }
	    // cout<<"---"<<'\n';
	    // for(const auto &i: noOfInitialValue)
	    //   {
	    // 	cout<<i<<'\n';
	    //   }
	    // // from=;
	    // // to=;

	    // cout<<"Move from "<<from<<" "<<to<<'\n';





	    // cout<<"Move to "<<from<<" "<<to-1<<'\n';




	    // k0(equation, k1, from, to);
	    // k(equation, k2, 0.5, k1, from, to);
	    // k(equation, k3, 0.5, k2, from, to);
	    // k(equation, k4, 1, k3, from, to);



	    // string aa;


	    // double v=0;
	    // for(uint16_t i=0; i<nx; i++)
	    //   {
	    // 	v+=y_n[i]+stepSize*(k1[i]+2*k2[i]+2*k3[i]+k4[i])/6;;
	    //   }
	    // cout<<"v "<<v<<'\n';

	    	    // uint16_t j=0;
	    // for(uint16_t i=equation.id*nx; i<(equation.id+1)*nx; i++)
	    //   {
	    // 	r[i]=y_n[j]+stepSize*(k1[j]+2*k2[j]+2*k3[j]+k4[j])/6;
	    // 	// r[i]=newValues[j]+stepSize*(k1[j]+2*k2[j]+2*k3[j]+k4[j])/6;
	    // 	cout<<i<<" "<<r[i]<<'\n';
	    // 	// y_n[i]=r[i]; // Set later
	    // 	// aa+=std::to_string(r[i]);
	    // 	// aa+=";";
	    // 	j++;
	    //   }
	    // j=0;
	    // cout<<aa<<'\n';
	    cout<<" "<<'\n';
	  }
	cout<<"++++++++++++++++++++++++++++++"<<'\n';
	// ao(edges, n, r);
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
