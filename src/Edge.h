#ifndef EDGE_H
#define EDGE_H

#include "Equation.h"

struct Edge
{
private:
  // Equations adding to vertex.
  vector<Equation> equationsAdd;
  // Equations subtracting from vertex.
  vector<Equation> equationsSubtract;
public:
  void AddToEquationsAdding(const Equation &e)
  {
    equationsAdd.emplace_back(e);
  }

  void AddToEquationsSubtracting(const Equation &e)
  {
    equationsSubtract.emplace_back(e);
  }

  double Calculate()
  {
    double result=0;

    for(Equation &e: equationsAdd)
      {
	result+=e.Calculate();
      }

    for(Equation &e: equationsSubtract)
      {
	result-=e.Calculate();
      }

    return result;
  }

  Edge(const uint16_t sizeAdd1, const uint16_t sizeSubtract1)
  {
    this->equationsAdd.reserve(sizeAdd1);
    this->equationsSubtract.reserve(sizeSubtract1);
  }

  Edge(){}
  ~Edge(){}
};

#endif
