#ifndef GRAPHEQUATION_H
#define GRAPHEQUATION_H

// #include "Graph.h"
#include <string>
#include <vector>
#include <cstdint>
#include "Edge.h"
#include "Vertex.h"
#include "Bools.h"
#include <map>
#include <unordered_map>
// #include "MathOperator.h"
// #include "Edge.h"

using std::unordered_map;
using std::map;
using std::string;
using std::vector;
#include <iostream>
using std::cout;

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
