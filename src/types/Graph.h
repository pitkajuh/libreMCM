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

  virtual ~Graph()
  {
    cout<<"~Graph() "<<vertices.size()<<" "<<edges.size()<<'\n';
    for(auto &i: vertices)
      {
	delete i;
      }

    for(auto &j: edges)
      {
	delete j;
      }
  }
};

class GraphEquation: public Graph
{
protected:
  template<typename T, typename U, typename L, typename I>
  void CreateVertex(const string &s1, const string &s2, const string &o)
  {
    cout<<"Create "<<'\n';
    VertexMultiValue *v=new VertexMultiValue(o);
    VertexValue *vertex1=new T(s1);
    VertexValue *vertex2=new U(s2);
    Edge *edge1=new L(vertex1, v);
    Edge *edge2=new I(vertex2, v);
    vertices.emplace_back(v);
    edges.emplace_back(edge1);
    edges.emplace_back(edge2);
  }

  void Simplify()
  {
    cout<<"simpli"<<'\n';
    for(auto &e: edges)
      {
	cout<<e<<'\n';
      }
  }

public:
  void CreateEdge(const string &s1, const string &s2, const string &o, const Bools &b1, const Bools &b2)
  {
    cout<<" "<<'\n';
    if(b1.variable and b2.variable)
      {
	CreateVertex<VertexVariable, VertexVariable, EdgeVariable, EdgeVariable>(s1, s2, o);
      }
    else if(b1.variable and b2.constant)
      {
	CreateVertex<VertexVariable, VertexConstant, EdgeVariable, EdgeConstant>(s1, s2, o);
      }
    else if(b1.variable and b2.numeric)
      {
	CreateVertex<VertexVariable, VertexNumeric, EdgeVariable, EdgeNumeric>(s1, s2, o);
      }
    else if(b1.constant and b2.variable)
      {
	CreateVertex<VertexConstant, VertexVariable, EdgeConstant, EdgeVariable>(s1, s2, o);
      }
    else if(b1.constant and b2.constant)
      {
	CreateVertex<VertexConstant, VertexConstant, EdgeConstant, EdgeConstant>(s1, s2, o);
      }
    else if(b1.constant and b2.numeric)
      {
	CreateVertex<VertexConstant, VertexNumeric, EdgeConstant, EdgeNumeric>(s1, s2, o);
      }
    else if(b1.numeric and b2.variable)
      {
	CreateVertex<VertexNumeric, VertexVariable, EdgeNumeric, EdgeVariable>(s1, s2, o);
      }
    else if(b1.numeric and b2.constant)
      {
	CreateVertex<VertexNumeric, VertexConstant, EdgeNumeric, EdgeConstant>(s1, s2, o);
      }
    else if(b1.numeric and b2.numeric)
      {
	CreateVertex<VertexNumeric, VertexNumeric, EdgeNumeric, EdgeNumeric>(s1, s2, o);
	// MathOperation *m=CreateNewMathOperation<Numeric, Numeric, NumericNumeric>(s1, s2, o);
	// // Result of numeric-numeric math operation can be calculated in advance, so the equation template can
	// // simplified and performance of the calculation increased.
	// m->Calculate();
	// cout<<"result "<<m->result<<'\n';
	// return m;
      }
    else if(b1.math and b2.math)
      {
	cout<<"b1.math and b2.math "<<stoi(s1.substr(1, s1.size()))<<" "<<stoi(s2.substr(1, s2.size()))<<" "<<edges.size()<<'\n';
	const uint8_t i1=stoi(s1.substr(1, s1.size()));
	const uint8_t i2=stoi(s2.substr(1, s2.size()));
	// GetEdges(stoi(s1.substr(1, s1.size())));

	Edge *E=new EdgeEdge(edges[i1], edges[i1+1], edges[i2], edges[i2+1]);
	edges.emplace_back(E);
	// Edge *edge1;
	// Edge *edge2;
      }
    else if(b1.math)
      {
	cout<<"b1.math"<<'\n';
      }
    else if(b2.math)
      {
	cout<<"b2.math"<<'\n';
      }
    else if(!b1.variable and !b1.constant and !b1.numeric and !b1.math)
      {
	throw std::invalid_argument("Value \""+s1+"\" is not a constant, variable or numeric value.");
      }
    else
      {
	throw std::invalid_argument("Value \""+s2+"\" is not a constant, variable or numeric value.");
      }

    // this->Simplify();
    // SetId(id);
    // CreateEdge1(s1, s2, o);
    // delete edge;
  }
  GraphEquation(){}
  ~GraphEquation(){cout<<"~GraphEquation"<<'\n';}
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
