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
#include "Vertex.h"
#include "Bools.h"
#include <map>

using std::map;
using std::string;
using std::vector;
#include <iostream>
using std::cout;

class Graph
{
protected:
  // vector<Vertex*> vertices;
  map<string, Vertex*> vmap;
  // vector<Edge*> edges;
public:

  virtual ~Graph()
  {
    // cout<<"~Graph() "<<vertices.size()<<" "<<edges.size()<<'\n';
    // for(auto &i: vertices)
    //   {
    // 	delete i;
    //   }
    // cout<<vmap.size()<<'\n';
    for(auto &[i1, i2]: vmap)
      {
	// cout<<"delete "<<i1<<" "<<i2<<'\n';
	delete i2;
      }

    // for(auto &j: edges)
    //   {
    // 	delete j;
    //   }
  }
};

class GraphEquation: public Graph
{
protected:
  bool IsInMap(const string &s);
  void AddToMap(Vertex *v, const string &s);

  template<typename T, typename U>
  void CreateVertexNumeric(const string &s1, const string &s2, const string &mathOperator, const uint8_t id);

  template<typename T, typename U, typename L, typename I>
  void CreateVertex(const string &s1, const string &s2, const string &mathOperator, const uint8_t id);

public:
  void CreateEdge(const string &s1, const string &s2, const string &mathOperator, const Bools &b1, const Bools &b2, const uint8_t id);
  GraphEquation(){}
  ~GraphEquation(){cout<<"~GraphEquation "<<'\n';}
};

class GraphEquationSingle: public GraphEquation
{
protected:
  VertexValue *vertex=nullptr;

  void CreateEdge(const Bools &b, const string &e)
  {
    if(b.variable){vertex=new VertexVariable(e);}
    else if(b.constant){vertex=new VertexConstant(e);}
    else{vertex=new VertexNumeric(e);}
  }
public:
  GraphEquationSingle(){}
  GraphEquationSingle(const Bools &b, const string &e)
  {
    this->CreateEdge(b, e);
  }
  ~GraphEquationSingle(){delete vertex;}
};

#endif
