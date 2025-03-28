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
#include "Bools.h"

using std::string;
using std::vector;
#include <iostream>
using std::cout;

class Graph
{
protected:
  vector<Vertex*> vertices;
  vector<Edge*> edges;
public:
  virtual ~Graph(){}
};

class GraphEquation: public Graph
{
protected:
  template<typename T, typename U>
  void CreateVertex(const string &s1, const string &s2, const string &o)
  {
    VertexMultiValue *v1=new VertexMultiValue(o);
    // Edge *v=new L;
    // VertexValue *vertex1=new T(s1);
    // VertexValue *vertex2=new U(s2);
    // Edge *edge1=new Edge(vertex1, v);
    // Edge *edge2=new Edge(vertex2, v);
    // vertices.emplace_back(v);
    // vertices.emplace_back(vertex1);
    // vertices.emplace_back(vertex2);
    // edges.emplace_back(edge1);
    // edges.emplace_back(edge2);
    delete v1;
    // delete v;
  }
public:
  void CreateEdge(const string &s1, const string &s2, const string &o, const Bools &b1, const Bools &b2, const uint8_t id)
  {
    // EdgeMathOperation *edge=nullptr;

    if(b1.variable and b2.variable)
      {
	CreateVertex<VertexVariable, VertexVariable>(s1, s2, o);
      }
    else if(b1.variable and b2.constant)
      {
	CreateVertex<VertexVariable, VertexConstant>(s1, s2, o);
      }
    else if(b1.variable and b2.numeric)
      {
	CreateVertex<VertexVariable, VertexNumeric>(s1, s2, o);
      }
    else if(b1.constant and b2.variable)
      {
	CreateVertex<VertexConstant, VertexVariable>(s1, s2, o);
      }
    else if(b1.constant and b2.constant)
      {
	CreateVertex<VertexConstant, VertexConstant>(s1, s2, o);
      }
    else if(b1.constant and b2.numeric)
      {
	CreateVertex<VertexConstant, VertexNumeric>(s1, s2, o);
      }
    else if(b1.numeric and b2.variable)
      {
	CreateVertex<VertexNumeric, VertexVariable>(s1, s2, o);
      }
    else if(b1.numeric and b2.constant)
      {
	CreateVertex<VertexNumeric, VertexConstant>(s1, s2, o);
      }
    else
      {
	CreateVertex<VertexNumeric, VertexNumeric>(s1, s2, o);
	// MathOperation *m=CreateNewMathOperation<Numeric, Numeric, NumericNumeric>(s1, s2, o);
	// // Result of numeric-numeric math operation can be calculated in advance, so the equation template can
	// // simplified and performance of the calculation increased.
	// m->Calculate();
	// cout<<"result "<<m->result<<'\n';
	// return m;
      }
    // SetId(id);
    // CreateEdge1(s1, s2, o);
    // delete edge;
  }
  GraphEquation(){}
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
  GraphEquationSingle(const Bools &b, const string &e, const uint8_t id)
  {
    // this->id=id;
    this->CreateEdge(b, e);
    this->vertex=vertex;
  }
  ~GraphEquationSingle(){delete vertex;}
};

#endif
