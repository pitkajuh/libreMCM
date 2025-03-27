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
  uint8_t id;
  Vertex *vertex1=nullptr;
  Vertex *vertex2=nullptr;
public:

  void SetId(uint8_t id){this->id=id;}
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

class EdgeVariableVariable: public Edge
{
protected:

public:
};

class EdgeVariableConstant: public Edge
{
protected:

public:
};

class EdgeVariableNumeric: public Edge
{
protected:

public:
};

class EdgeConstantVariable: public Edge
{
protected:

public:
};

class EdgeConstantConstant: public Edge
{
protected:

public:
};

class EdgeConstantNumeric: public Edge
{
protected:

public:
};

class EdgeNumericVariable: public Edge
{
protected:

public:
};

class EdgeNumericConstant: public Edge
{
protected:

public:
};

class EdgeNumericNumeric: public Edge
{
protected:

public:
};


#endif
