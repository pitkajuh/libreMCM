#ifndef EDGE_H
#define EDGE_H

#include "Equation.h"

struct Edge
{
public:
  vector<Equation> equationsAdd;
  vector<Equation> equationsSubtract;
  uint16_t sizeAdd;
  uint16_t sizeSubtract;

  double Calculate()
  {
    double result=0;

    for(uint16_t i=0; i<this->sizeAdd; i++)
      {
	result+=this->equationsAdd[i].Calculate();
      }

    for(uint16_t i=0; i<this->sizeSubtract; i++)
      {
	result-=this->equationsSubtract[i].Calculate();
      }

    return result;
  }

  Edge(const uint16_t sizeAdd1, const uint16_t sizeSubtract1)
  {
    this->sizeAdd=sizeAdd1;
    this->sizeSubtract=sizeSubtract1;
    this->equationsAdd.reserve(sizeAdd1);
    this->equationsSubtract.reserve(sizeSubtract1);
  }

  Edge(){}
  ~Edge(){}
};

#endif
