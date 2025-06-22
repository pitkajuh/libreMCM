#ifndef EDGE_H
#define EDGE_H

#include "Equation.h"

struct Edge
{
private:
  void a(const vector<uint16_t> &noivs, const vector<uint16_t> &noOfInitialValue)
  {
    cout<<"FROM "<<from<<" TO "<<to<<'\n';

    uint16_t from1=noOfInitialValue[from]-noivs[from];
    uint16_t to1=noOfInitialValue[to]-noivs[to];

    uint16_t f1=from1+noivs[from];
    uint16_t t1=to1+noivs[to];
    cout<<"f1 "<<f1<<" t1 "<<t1<<'\n';
    if(noivs[from]>noivs[to])
      {
	// cout<<"noivs[from]>noivs[to] "<<noivs[from]<<" "<<noivs[to]<<'\n';
	// cout<<"noOfInitialValue[from]>noOfInitialValue[to] "<<noOfInitialValue[from]<<" "<<noOfInitialValue[to]<<'\n';
	// cout<<noOfInitialValue[from]-noOfInitialValue[to]<<'\n';

	if(noOfInitialValue[from]-noOfInitialValue[to]>from1)
	  {
	    f1-=noivs[to];
	  }
	else
	  {
	    from1+=noivs[to];
	  }

      }
    else
      {
	// cout<<"noivs[from]<noivs[to] "<<noivs[from]<<" "<<noivs[to]<<'\n';
	// cout<<noOfInitialValue[from]<<" "<<noOfInitialValue[to]<<'\n';
	// cout<<noOfInitialValue[to]-noOfInitialValue[from]<<'\n';

	if(to1>f1)
	  {
	    // cout<<"to1>f1"<<'\n';
	    t1-=f1;
	  }
	else
	  {
	    // cout<<"ELSE"<<'\n';
	    // f1-=t1;
	    to1+=from1;
	  }
      }



    const std::pair<uint16_t, uint16_t> p1{from1, f1};
    const std::pair<uint16_t, uint16_t> p2{to1, t1};
    // cout<<"From1 "<<from1<<" to1 "<<to1<<'\n';
    cout<<p1.first<<" "<<p1.second<<'\n';
    cout<<p2.first<<" "<<p2.second<<'\n';
    // for(uint16_t i=0; i<noivs.size(); i++)
    //   {
    // 	cout<<noivs[i]<<" "<<noOfInitialValue[i]<<" "<<noOfInitialValue[i]-noivs[i]<<'\n';
    //   }
    cout<<" "<<'\n';
  }
public:
  Equation *equation=nullptr;
  uint16_t from;
  uint16_t to;

  Edge(){}
  Edge(Equation *equation, const uint16_t from, const uint16_t to, const vector<uint16_t> &noivs, const vector<uint16_t> &noOfInitialValue)
  {
    this->equation=equation;
    this->from=from;
    this->to=to;
    a(noivs, noOfInitialValue);
  }
  virtual ~Edge(){}
};

#endif
