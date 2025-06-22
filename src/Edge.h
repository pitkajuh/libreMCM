#ifndef EDGE_H
#define EDGE_H

#include "Equation.h"

struct Edge
{
private:
  void a(const vector<uint16_t> &noivs, const vector<uint16_t> &noOfInitialValue, const uint16_t from, const uint16_t to)
  {
    cout<<"FROM "<<from<<" TO "<<to<<'\n';

    uint16_t from1=noOfInitialValue[from]-noivs[from];
    uint16_t to1=noOfInitialValue[to]-noivs[to];

    uint16_t f1=from1+noivs[from];
    uint16_t t1=to1+noivs[to];
    cout<<"f1 "<<f1<<" t1 "<<t1<<'\n';
    if(noivs[from]>noivs[to])
      {
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
	if(to1>f1)
	  {
	    t1-=f1;
	  }
	else
	  {
	    to1+=from1;
	  }
      }
    p1={from1, f1};
    p2={to1, t1};
    // const std::pair<uint16_t, uint16_t> p1{from1, f1};
    // const std::pair<uint16_t, uint16_t> p2{to1, t1};
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
  // uint16_t from;
  // uint16_t to;
  std::pair<uint16_t, uint16_t> p1;
  std::pair<uint16_t, uint16_t> p2;

  Edge(){}
  Edge(Equation *equation, const uint16_t from, const uint16_t to, const vector<uint16_t> &noivs, const vector<uint16_t> &noOfInitialValue)
  {
    this->equation=equation;
    a(noivs, noOfInitialValue, from, to);
  }
  virtual ~Edge(){}
};

#endif
