#ifndef GRAPH_H
#define GRAPH_H

#include "Vertex.h"
#include "Edge.h"

class Graph
{
private:
  vector<Vertex> vertices;
  vector<Edge> edges;
public:
  void AddVertex(const Vertex &v)
  {
    vertices.emplace_back(v);
  }

  void AddEdge(const Edge &e)
  {
    edges.emplace_back(e);
  }

  Graph(){}
  virtual ~Graph(){}
};

#endif
