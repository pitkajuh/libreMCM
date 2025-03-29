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
    // for(auto &i: vertices)
    //   {
    // 	delete i;
    //   }

    // for(auto &j: edges)
    //   {
    // 	delete j;
    //   }
  }
};

class GraphEquation: public Graph
{
protected:
  template<typename T, typename U, typename L, typename I>
  void CreateVertex(const string &s1, const string &s2, const string &o)
  {
    cout<<"Create"<<'\n';
    VertexMultiValue *v=new VertexMultiValue(o);
    VertexValue *vertex1=new T(s1);
    VertexValue *vertex2=new U(s2);
    Edge *edge1=new L(vertex1, v);
    Edge *edge2=new I(vertex2, v);
    cout<<edge1<<" "<<edge2<<'\n';
    // vertices.emplace_back(v);
    // edges.emplace_back(edge1);
    // edges.emplace_back(edge2);
    delete edge1;
    delete edge2;
    delete v;
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
    else
      {
	CreateVertex<VertexNumeric, VertexNumeric, EdgeNumeric, EdgeNumeric>(s1, s2, o);
	// MathOperation *m=CreateNewMathOperation<Numeric, Numeric, NumericNumeric>(s1, s2, o);
	// // Result of numeric-numeric math operation can be calculated in advance, so the equation template can
	// // simplified and performance of the calculation increased.
	// m->Calculate();
	// cout<<"result "<<m->result<<'\n';
	// return m;
      }
    // this->Simplify();
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
  GraphEquationSingle(const Bools &b, const string &e)
  {
    this->CreateEdge(b, e);
  }
  ~GraphEquationSingle(){delete vertex;}
};

#endif
