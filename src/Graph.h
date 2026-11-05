#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
#include "Vertex.h"
#include "Edge.h"

class Graph
{
private:
  vector<Vertex> vertices;
  vector<Edge> edges;
public:
  void PrintGraph()
  {
    for(auto &i: vertices)
      {
	i.PrintVertex();
      }
  }

  Vertex& GetVertex(const string &name)
  {
    return *std::find_if(vertices.begin(), vertices.end(),
			[name](const Vertex &v){return v.GetName()==name;}
			);
  }

  Vertex& GetVertex(const uint8_t &id)
  {
    return *std::find_if(vertices.begin(), vertices.end(),
			[id](Vertex &v){return v.GetId()==id;}
			);
  }

  bool FindVertex(const string &name)
  {
    return std::find_if(vertices.begin(), vertices.end(),
			[name](Vertex &v){return v.GetName()==name;}
			)!=vertices.end();
  }

  void AddVertex(const Vertex &v)
  {
    vertices.emplace_back(v);
  }

  void AddEdge(const Edge &e)
  {
    edges.emplace_back(e);
  }

  vector<Edge>& GetEdges()
  {
    return edges;
  }

  Graph(){}
  ~Graph(){}
};

#endif
