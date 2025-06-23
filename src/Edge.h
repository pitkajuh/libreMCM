#ifndef EDGE_H
#define EDGE_H

#include "Equation.h"

struct Edge
{
private:
  void a(const vector<uint16_t> &noivs, const vector<uint16_t> &noOfInitialValue, const uint16_t from, const uint16_t to)
  {
    uint16_t from1=noOfInitialValue[from]-noivs[from];
    uint16_t to1=noOfInitialValue[to]-noivs[to];
    uint16_t f1=from1+noivs[from];
    uint16_t t1=to1+noivs[to];

    // for(uint16_t i=0; i<4; i++)
    //   {
    // 	cout<<noivs[i]<<" "<<noOfInitialValue[i]<<'\n';
    //   }
    // cout<<" "<<'\n';
    if(from==to)
      {
	to1=from1;
	t1=f1;
      }
    else if(noivs[from]>noivs[to])
      {
	if(noOfInitialValue[from]-noOfInitialValue[to]>from1) f1-=noivs[to];
	else from1+=noivs[to];
      }
    else
      {
	if(to1>f1) t1-=f1;
	else to1+=from1;
      }
    p1={from1, f1};
    p2={to1, t1};
  }
public:
  Equation *equation=nullptr;
  pair<uint16_t, uint16_t> p1;
  pair<uint16_t, uint16_t> p2;

  Edge(){}
  Edge(Equation *equation, const uint16_t from, const uint16_t to, const vector<uint16_t> &noivs, const vector<uint16_t> &noOfInitialValue)
  {
    this->equation=equation;
    a(noivs, noOfInitialValue, from, to);
  }
  virtual ~Edge(){}
};

#endif
