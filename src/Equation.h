#ifndef EQUATION_H
#define EQUATION_H

#include <cstdint>
#include "MathOperation.h"

struct Equation
{
public:
  uint16_t id;
  vector<MathOperation> vertices;

  double Calculate()
  {
    for(auto &i: vertices)
      {
	i.Calculate();
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
