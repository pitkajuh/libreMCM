/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <cstdint>
#include "Edge.h"

using std::string;
using std::vector;
#include <iostream>
using std::cout;

class Graph
{
private:
  vector<Edge*> edges;
public:
  virtual ~Graph(){}
};

class GraphEquation: public Graph
{
private:

public:
  void CreateEdge(const string &s1, const string &s2, const string &o)
  {
    Edge *edge=new EdgeMathOperation;
    delete edge;
  }
  GraphEquation(){}
  // GraphEquation(VertexValue *vertex)
  // {
  //   this->vertex=vertex;
  // }
};

class GraphEquationSingle: public GraphEquation
{
private:
  VertexValue *vertex=nullptr;
public:

  GraphEquationSingle(){}
  GraphEquationSingle(VertexValue *vertex)
  {
    this->vertex=vertex;
  }
  ~GraphEquationSingle(){delete vertex;}
};

#endif
