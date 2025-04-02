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
  bool IsInMap(const string &s){return vmap.count(s)>0;}
  void AddToMap(Vertex *v, const string &s)
  {
    if(!IsInMap(s)) vmap[s]=v;
    else cout<<"AA "<<vmap[s]<<'\n';
  }

  template<typename T, typename U, typename L, typename I>
  void CreateVertex(const string &s1, const string &s2, const string &mathOperator, const uint8_t id)
  {
    cout<<"Create "<<id<<'\n';
    Vertex *vertex1=nullptr;
    Vertex *vertex2=nullptr;

    if(!IsInMap(s1))
      {
	vertex1=new T(s1);
	AddToMap(vertex1, s1);
      }
    else vertex1=vmap[s1];

    if(!IsInMap(s2))
      {
	vertex2=new T(s2);
	AddToMap(vertex2, s2);
      }
    else vertex2=vmap[s2];

    VertexVertices *v=new VertexVertices(vertex1, vertex2, mathOperator);
    // Edge *edge1=new L(vertex1, v);
    // Edge *edge2=new I(vertex2, v);
    cout<<s1<<" "<<s2<<" "<<"@"<<std::to_string(id)<<'\n';
    // cout<<vmap[s1]<<" "<<vmap.find(s1)<<'\n';


    // vmap[s1]=vertex1;
    // vmap[s2]=vertex2;
    // vertices.emplace_back(v);
    vmap["@"+std::to_string(id)]=v;
    // edges.emplace_back(edge1);
    // edges.emplace_back(edge2);
    cout<<vertex1<<" "<<vertex2<<'\n';
    cout<<"Created"<<'\n';
  }

  void Simplify(const uint8_t id)
  {
    cout<<"ID "<<std::to_string(id)<<'\n';
    // vmap.end()->second->Calculate();
    // cout<<"simplify "<<vmap.end()->second->GetValue()<<'\n';

    // Remove vertex at vertices.back()
    // Create a new Vertex VertexNumeric
  }
public:
  void CreateEdge(const string &s1, const string &s2, const string &mathOperator, const Bools &b1, const Bools &b2, const uint8_t id)
  {
    cout<<" "<<'\n';
    if(b1.variable and b2.variable)
      {
	CreateVertex<VertexVariable, VertexVariable, EdgeVariable, EdgeVariable>(s1, s2, mathOperator, id);
      }
    else if(b1.variable and b2.constant)
      {
	CreateVertex<VertexVariable, VertexConstant, EdgeVariable, EdgeConstant>(s1, s2, mathOperator, id);
      }
    else if(b1.variable and b2.numeric)
      {
	CreateVertex<VertexVariable, VertexNumeric, EdgeVariable, EdgeNumeric>(s1, s2, mathOperator, id);
      }
    else if(b1.constant and b2.variable)
      {
	CreateVertex<VertexConstant, VertexVariable, EdgeConstant, EdgeVariable>(s1, s2, mathOperator, id);
      }
    else if(b1.constant and b2.constant)
      {
	CreateVertex<VertexConstant, VertexConstant, EdgeConstant, EdgeConstant>(s1, s2, mathOperator, id);
      }
    else if(b1.constant and b2.numeric)
      {
	CreateVertex<VertexConstant, VertexNumeric, EdgeConstant, EdgeNumeric>(s1, s2, mathOperator, id);
      }
    else if(b1.numeric and b2.variable)
      {
	CreateVertex<VertexNumeric, VertexVariable, EdgeNumeric, EdgeVariable>(s1, s2, mathOperator, id);
      }
    else if(b1.numeric and b2.constant)
      {
	CreateVertex<VertexNumeric, VertexConstant, EdgeNumeric, EdgeConstant>(s1, s2, mathOperator, id);
      }
    else if(b1.numeric and b2.numeric)
      {
	VertexValue *vertex1=new VertexNumeric(s1);
	VertexValue *vertex2=new VertexNumeric(s2);
	VertexVertices *v=new VertexVertices(vertex1, vertex2, mathOperator);
	v->Calculate();
	VertexValue *calculated=new VertexNumeric(v->GetValue());

	vmap["@"+std::to_string(id)]=calculated;
	delete vertex1;
	delete vertex2;
	delete v;
	cout<<calculated<<'\n';
	// // Result can be calculated in advance, so the equation template can
	// // simplified and performance of the calculation increased.
      }
    else if(b1.math and b2.math)
      {
	cout<<"b1.math and b2.math "<<'\n';
	// const uint8_t i1=stoi(s1.substr(1, s1.size()));
	// const uint8_t i2=stoi(s2.substr(1, s2.size()));

	VertexVertices *v1=new VertexVertices(vmap[s1], vmap[s2], mathOperator);
	// Edge *edge1=new Edge2(vertices[i1], v1);
	// Edge *edge2=new Edge2(vertices[i2], v1);
	cout<<v1<<'\n';
	// vertices.emplace_back(v1);
	vmap["@"+std::to_string(id)]=v1;
	// edges.emplace_back(edge1);
	// edges.emplace_back(edge2);
      }
    else if(b1.math)
      {
	cout<<"b1.math"<<'\n';
	// const uint8_t i1=stoi(s1.substr(1, s1.size()));
	VertexVertices *v1=new VertexVertices(vmap[s1], vmap[s2], mathOperator);
	vmap["@"+std::to_string(id)]=v1;
	// vertices.emplace_back(v1);
	// Edge *E=new EdgeEdge1(edges[i1], edges[i1+1], vmap[s2]);
	// edges.emplace_back(E);
      }
    else if(b2.math)
      {
	cout<<"b2.math"<<'\n';
	// const uint8_t i2=stoi(s2.substr(1, s2.size()));
	VertexVertices *v2=new VertexVertices(vmap[s2], vmap[s1], mathOperator);
	// vertices.emplace_back(v2);
	vmap["@"+std::to_string(id)]=v2;
      }
    else if(!b1.variable and !b1.constant and !b1.numeric and !b1.math)
      {
	throw std::invalid_argument("Value \""+s1+"\" is not a constant, variable or numeric value.");
      }
    else
      {
	throw std::invalid_argument("Value \""+s2+"\" is not a constant, variable or numeric value.");
      }

    // SetId(id);
    // CreateEdge1(s1, s2, mathOperator);
    // delete edge;
  }
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
