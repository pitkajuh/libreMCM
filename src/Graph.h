#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
#include <fstream>
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

  double GetResult(const uint16_t vertex_id) const
  {
    return vertices[vertex_id].GetLastValue();
  }

  vector<double> GetLatestResults()
  {
    vector<double> latestResults(GetNumberOfVertices());

    for(uint16_t vertex_id=0; vertex_id<GetNumberOfVertices(); vertex_id++)
      {
	latestResults[vertex_id]=vertices[vertex_id].GetLastValue();
      }
    return latestResults;
  }

  uint16_t GetNumberOfVertices() const
  {
    return vertices.size();
  }

  void WriteResults()
  {
    for(Vertex &vertex: vertices)
      {
	std::ofstream file(vertex.GetName()+".txt");

	for(double d: vertex.GetValues())
	  {
	    file<<d;
	  }
	file.close();
      }
  }

  void AddResults(const vector<double> &results)
  {
    for(uint16_t vertex_id=0; vertex_id<GetNumberOfVertices(); vertex_id++)
      {
	vertices[vertex_id].AddValue(results[vertex_id]);
      }
  }

  Vertex& GetVertex(const string &name)
  {
    return *std::find_if(vertices.begin(), vertices.end(),
			[name](const Vertex &v){return v.GetName()==name;}
			);
  }

  Vertex& GetVertex(const uint16_t &id)
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

  void AddVertex(const Vertex &vertex)
  {
    vertices.emplace_back(vertex);
  }

  void AddEdge(const Edge &edge)
  {
    edges.emplace_back(edge);
  }

  vector<Edge>& GetEdges()
  {
    return edges;
  }

  Graph(){}
  ~Graph(){}
};

#endif
