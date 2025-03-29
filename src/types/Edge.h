/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef EDGE_H
#define EDGE_H

#include "Vertex.h"
#include <iostream>
using std::cout;

class Edge
{
protected:
  Vertex *vertex1=nullptr;
  Vertex *vertex2=nullptr;
public:
  Edge(){}
  virtual ~Edge()
  {
    cout<<"~Edge()"<<'\n';
    delete vertex1;
  };
};

class EdgeEquation: public Edge
{
public:
  EdgeEquation(){}
  ~EdgeEquation(){}
};

class EdgeVariable: public EdgeEquation
{
public:
  EdgeVariable(){}
  EdgeVariable(Vertex *vertex1, VertexMultiValue *vertex2)
  {
    this->vertex1=vertex1;
    this->vertex2=vertex2;
  }
  ~EdgeVariable(){}
};

class EdgeConstant: public EdgeEquation
{
public:
  EdgeConstant(){}
  EdgeConstant(Vertex *vertex1, VertexMultiValue *vertex2)
  {
    this->vertex1=vertex1;
    this->vertex2=vertex2;
  }
  ~EdgeConstant(){}
};

class EdgeNumeric: public EdgeEquation
{
public:
  EdgeNumeric(){}
  EdgeNumeric(Vertex *vertex1, VertexMultiValue *vertex2)
  {
    this->vertex1=vertex1;
    this->vertex2=vertex2;
  }
  ~EdgeNumeric(){}
};

#endif
