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
public:
  Edge(){}
  virtual ~Edge(){}
};

class Edge1: public Edge
{
protected:
  Vertex *vertex1=nullptr;
  Vertex *vertex2=nullptr;
public:
  Edge1(){}
  virtual ~Edge1()
  {
    cout<<"~Edge1()"<<'\n';
    delete vertex1;
  };
};

class EdgeEquation: public Edge1
{
public:
  EdgeEquation(){}
  ~EdgeEquation(){}
};

class Edge2: public EdgeEquation
{
public:
  Edge2(){}
  Edge2(Vertex *vertex1, Vertex *vertex2)
  {
    this->vertex1=vertex1;
    this->vertex2=vertex2;
  }
  ~Edge2(){}
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
