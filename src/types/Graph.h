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
  vector<Edge*> edges;
public:
  virtual ~Graph(){}
};

class GraphEquation: public Graph
{
public:
  void CreateEdge(const string &s1, const string &s2, const string &o, const Bools &b1, const Bools &b2, const uint8_t id)
  {
    EdgeMathOperation *edge=nullptr;

    if(b1.variable and b2.variable)
      {
	edge->CreateEdge<VertexVariable, VertexVariable, EdgeVariableVariable>(s1, s2, o);
      }
    else if(b1.variable and b2.constant)
      {
	edge->CreateEdge<VertexVariable, VertexConstant, EdgeVariableConstant>(s1, s2, o);
      }
    else if(b1.variable and b2.numeric)
      {
	edge->CreateEdge<VertexVariable, VertexNumeric, EdgeVariableNumeric>(s1, s2, o);
      }
    else if(b1.constant and b2.variable)
      {
	edge->CreateEdge<VertexConstant, VertexVariable, EdgeConstantVariable>(s1, s2, o);
      }
    else if(b1.constant and b2.constant)
      {
	edge->CreateEdge<VertexConstant, VertexConstant, EdgeConstantConstant>(s1, s2, o);
      }
    else if(b1.constant and b2.numeric)
      {
	edge->CreateEdge<VertexConstant, VertexNumeric, EdgeConstantNumeric>(s1, s2, o);
      }
    else if(b1.numeric and b2.variable)
      {
	edge->CreateEdge<VertexNumeric, VertexVariable, EdgeNumericVariable>(s1, s2, o);
      }
    else if(b1.numeric and b2.constant)
      {
	edge->CreateEdge<VertexNumeric, VertexConstant, EdgeNumericConstant>(s1, s2, o);
      }
    else
      {
	edge->CreateEdge<VertexNumeric, VertexNumeric, EdgeNumericNumeric>(s1, s2, o);
	// MathOperation *m=CreateNewMathOperation<Numeric, Numeric, NumericNumeric>(s1, s2, o);
	// // Result of numeric-numeric math operation can be calculated in advance, so the equation template can
	// // simplified and performance of the calculation increased.
	// m->Calculate();
	// cout<<"result "<<m->result<<'\n';
	// return m;
      }
    edge->SetId(id);
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
