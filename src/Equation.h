#ifndef EQUATION_H
#define EQUATION_H

#include <cstdint>
#include "MathOperation.h"

struct Equation
{
public:
  uint16_t id;
  vector<MathOperation> vertices;
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

};

#endif
