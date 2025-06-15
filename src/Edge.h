#ifndef EDGE_H
#define EDGE_H

#include "Equation.h"

struct Edge
{
public:
  Equation *equation=nullptr;
  uint16_t from;
  uint16_t to;

  Edge(){}
  Edge(Equation *equation, const uint16_t from, const uint16_t to)
  {
    cout<<"FROM "<<from<<" "<<"TO "<<to<<'\n';
    this->equation=equation;
    this->from=from;
    this->to=to;
  }
  virtual ~Edge(){}
};

#endif
