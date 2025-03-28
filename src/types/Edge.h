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
#include "../global/mathconst.h"

using std::string;
using std::vector;
#include <iostream>
using std::cout;

class Edge
{
protected:
  Vertex *vertex1=nullptr;
  Vertex *vertex2=nullptr;
public:

  Edge(){}
  Edge(Vertex *vertex1, Vertex *vertex2)
  {
    this->vertex1=vertex1;
    this->vertex2=vertex2;
  }
  ~Edge()
  {
    delete vertex1;
    delete vertex2;
  }
};

class EdgeEquation: public Edge
{
protected:

public:

};

class EdgeVariable: public EdgeEquation
{
protected:

public:
  EdgeVariable(){}
  EdgeVariable(Vertex *vertex1, VertexMultiValue *vertex2)
  {
    this->vertex1=vertex1;
    this->vertex2=vertex2;
  }
};

class EdgeConstant: public EdgeEquation
{
protected:

public:
  EdgeConstant(){}
  EdgeConstant(Vertex *vertex1, VertexMultiValue *vertex2)
  {
    this->vertex1=vertex1;
    this->vertex2=vertex2;
  }
};

class EdgeNumeric: public EdgeEquation
{
protected:

public:
  EdgeNumeric(){}
  EdgeNumeric(Vertex *vertex1, VertexMultiValue *vertex2)
  {
    this->vertex1=vertex1;
    this->vertex2=vertex2;
  }
};










// class EdgeConstantVariable: public Edge
// {
// protected:

// public:
//   EdgeConstantVariable(){}
//   EdgeConstantVariable(Vertex *vertex1, Vertex *vertex2)
//   {
//     this->vertex1=vertex1;
//     this->vertex2=vertex2;
//   }
// };

// class EdgeConstantConstant: public Edge
// {
// protected:

// public:
//   EdgeConstantConstant(){}
//   EdgeConstantConstant(Vertex *vertex1, Vertex *vertex2)
//   {
//     this->vertex1=vertex1;
//     this->vertex2=vertex2;
//   }
// };

// class EdgeConstantNumeric: public Edge
// {
// protected:

// public:
//   EdgeConstantNumeric(){}
//   EdgeConstantNumeric(Vertex *vertex1, Vertex *vertex2)
//   {
//     this->vertex1=vertex1;
//     this->vertex2=vertex2;
//   }
// };

// class EdgeNumericVariable: public Edge
// {
// protected:

// public:
//   EdgeNumericVariable(){}
//   EdgeNumericVariable(Vertex *vertex1, Vertex *vertex2)
//   {
//     this->vertex1=vertex1;
//     this->vertex2=vertex2;
//   }
// };

// class EdgeNumericConstant: public Edge
// {
// protected:

// public:
//   EdgeNumericConstant(){}
//   EdgeNumericConstant(Vertex *vertex1, Vertex *vertex2)
//   {
//     this->vertex1=vertex1;
//     this->vertex2=vertex2;
//   }
// };

// class EdgeNumericNumeric: public Edge
// {
// protected:

// public:
//   EdgeNumericNumeric(){}
//   EdgeNumericNumeric
//   (Vertex *vertex1, Vertex *vertex2)
//   {
//     this->vertex1=vertex1;
//     this->vertex2=vertex2;
//   }
// };


#endif
