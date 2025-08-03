#ifndef EQUATION_H
#define EQUATION_H

#include <cstdint>
#include "Vertex.h"

struct Equation
{
public:
  uint16_t id;
  vector<Vertex> vertices;

  double Calculate()
  {
    for(Vertex &vertex: vertices)
      {
	vertex.Calculate();
      }
    // cout<<"----------------"<<'\n';

    return *vertices.back().result;
  }
};

struct Equations
{
public:
  vector<Equation> equations;

  void Calculate()
  {
    for(Equation &equation: equations)
      {
	equation.Calculate();
      }
  }
};

#endif
