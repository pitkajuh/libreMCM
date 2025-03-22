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

#include <string>
#include <vector>
#include <cstdint>
#include "Vertex.h"

using std::string;
using std::vector;
#include <iostream>
using std::cout;

class Edge
{
private:
  Vertex *vertex1=nullptr;
  Vertex *vertex2=nullptr;
public:

  Edge(){}
  Edge(Vertex *&vertex1, Vertex *&vertex2)
  {
    this->vertex1=vertex1;
    this->vertex2=vertex2;
  }
};

class EdgeMathOperator: public Edge
{
private:

public:

};

#endif
