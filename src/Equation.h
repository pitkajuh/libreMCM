#ifndef EQUATION_H
#define EQUATION_H

#include <cstdint>
#include "Vertex.h"

struct Equation
{
public:
  uint16_t id;
  vector<Vertex> vertices;
  uint16_t size1;

  double Calculate()
  {
    for(uint16_t i=0; i<this->size1; i++)
      {
	vertices[i].Calculate();
      }
    return *vertices.back().result;
  }
};

struct Equations
{
public:
  vector<Equation> equations;

  void Calculate()
  {
    cout<<"EQUATIONS"<<'\n';
    for(Equation &equation: equations)
      {
	equation.Calculate();
      }
  }
};

#endif
