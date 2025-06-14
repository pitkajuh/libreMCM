#ifndef GRAPHEQUATION_H
#define GRAPHEQUATION_H

#include <cstdint>
#include "Vertex.h"

struct Equation
{
public:
  uint16_t id;
  vector<VertexNew> vertices;
};

struct Equations
{
public:
  vector<Equation> equations;
};

#endif
