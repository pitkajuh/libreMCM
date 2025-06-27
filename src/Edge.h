#ifndef EDGE_H
#define EDGE_H

#include "Equation.h"

struct Edge2
{
public:
  vector<Equation> equationsAdd;
  vector<Equation> equationsSubtract;

  double Calculate()
  {
    double result=0;

    for(Equation &equationAdd: equationsAdd)
      {
	result+=equationAdd.Calculate();
      }

    for(Equation &equationSubtract: equationsSubtract)
      {
	result-=equationSubtract.Calculate();
      }
    return result;
  }

  Edge2(const uint16_t sizeAdd, const uint16_t sizeSubtract)
  {
    equationsAdd.reserve(sizeAdd);
    equationsSubtract.reserve(sizeSubtract);
  }

  Edge2(){}
  ~Edge2(){}
};

#endif
