#ifndef GRAPH_H
#define GRAPH_H

#include "Vertex.h"
#include "Edge.h"

class Graph
{
public:
  vector<Vertex> vertices;
  vector<Edge> edges;
  Graph(){}
  virtual ~Graph(){}
};

#endif
