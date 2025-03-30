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
  vector<Vertex*> vertices;
  map<string, Vertex*> vmap;
  vector<Edge*> edges;
public:

  virtual ~Graph()
  {
    cout<<"~Graph() "<<vertices.size()<<" "<<edges.size()<<'\n';
    for(auto &i: vertices)
      {
	cout<<"delete "<<i<<'\n';
	delete i;
      }

    // for(auto &[i1, i2]: vmap)
    //   {
    // 	cout<<"delete "<<i2<<'\n';
    // 	delete i2;
    //   }

    for(auto &j: edges)
      {
	cout<<"delete "<<j<<'\n';
	delete j;
      }
  }
};

class GraphEquation: public Graph
{
protected:
  template<typename T, typename U, typename L, typename I>
  void CreateVertex(const string &s1, const string &s2, const string &mathOperator)
  {
    cout<<"Create "<<'\n';

    VertexValue *vertex1=new T(s1);
    VertexValue *vertex2=new U(s2);
    VertexMultiValue *v=new VertexVertices(vertex1, vertex2, mathOperator);
    Edge *edge1=new L(vertex1, v);
    Edge *edge2=new I(vertex2, v);

    vmap[s1]=vertex1;
    vmap[s2]=vertex2;
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
  void CreateEdge(const string &s1, const string &s2, const string &mathOperator, const Bools &b1, const Bools &b2)
  {
    cout<<" "<<'\n';
    if(b1.variable and b2.variable)
      {
	CreateVertex<VertexVariable, VertexVariable, EdgeVariable, EdgeVariable>(s1, s2, mathOperator);
      }
    else if(b1.variable and b2.constant)
      {
	CreateVertex<VertexVariable, VertexConstant, EdgeVariable, EdgeConstant>(s1, s2, mathOperator);
      }
    else if(b1.variable and b2.numeric)
      {
	CreateVertex<VertexVariable, VertexNumeric, EdgeVariable, EdgeNumeric>(s1, s2, mathOperator);
      }
    else if(b1.constant and b2.variable)
      {
	CreateVertex<VertexConstant, VertexVariable, EdgeConstant, EdgeVariable>(s1, s2, mathOperator);
      }
    else if(b1.constant and b2.constant)
      {
	CreateVertex<VertexConstant, VertexConstant, EdgeConstant, EdgeConstant>(s1, s2, mathOperator);
      }
    else if(b1.constant and b2.numeric)
      {
	CreateVertex<VertexConstant, VertexNumeric, EdgeConstant, EdgeNumeric>(s1, s2, mathOperator);
      }
    else if(b1.numeric and b2.variable)
      {
	CreateVertex<VertexNumeric, VertexVariable, EdgeNumeric, EdgeVariable>(s1, s2, mathOperator);
      }
    else if(b1.numeric and b2.constant)
      {
	CreateVertex<VertexNumeric, VertexConstant, EdgeNumeric, EdgeConstant>(s1, s2, mathOperator);
      }
    else if(b1.numeric and b2.numeric)
      {
	CreateVertex<VertexNumeric, VertexNumeric, EdgeNumeric, EdgeNumeric>(s1, s2, mathOperator);
	// MathOperation *m=CreateNewMathOperation<Numeric, Numeric, NumericNumeric>(s1, s2, mathOperator);
	// // Result of numeric-numeric math operation can be calculated in advance, so the equation template can
	// // simplified and performance of the calculation increased.
	// m->Calculate();
	// cout<<"result "<<m->result<<'\n';
	// return m;
      }
    else if(b1.math and b2.math)
      {
	cout<<"b1.math and b2.math "<<stoi(s1.substr(1, s1.size()))<<" "<<stoi(s2.substr(1, s2.size()))<<" "<<edges.size()<<" "<<vertices.size()<<'\n';
	const uint8_t i1=stoi(s1.substr(1, s1.size()));
	const uint8_t i2=stoi(s2.substr(1, s2.size()));

	Vertex *v1=new VertexVertices(vertices[i1], vertices[i2], mathOperator);
	// Edge *edge1=new Edge2(vertices[i1], v1);
	// Edge *edge2=new Edge2(vertices[i2], v1);
	vertices.emplace_back(v1);
	// edges.emplace_back(edge1);
	// edges.emplace_back(edge2);




	// delete v1;

	// Edge *E=new EdgeEdge(edges[i1], edges[i1+1], edges[i2], edges[i2+1]);
	// Vertex *v=new VertexMathVertex(E);
	// vertices.emplace_back(v);
	// edges.emplace_back(E);
      }
    else if(b1.math)
      {
	cout<<"b1.math"<<'\n';
	// const uint8_t i1=stoi(s1.substr(1, s1.size()));
	// Edge *E=new EdgeEdge1(edges[i1], edges[i1+1], vmap[s2]);
	// edges.emplace_back(E);
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
    // CreateEdge1(s1, s2, mathOperator);
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
