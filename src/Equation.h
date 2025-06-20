#ifndef GRAPHEQUATION_H
#define GRAPHEQUATION_H

#include <cstdint>
#include "Vertex.h"

struct Equation
{
public:
  uint16_t id;
  vector<VertexNew> vertices;

  void Calculate()
  {
    for(VertexNew &vertex: vertices)
      {
	vertex.Calculate();
	cout<<"Result is "<<*vertex.result<<'\n';
      }
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
