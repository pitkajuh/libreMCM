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
  ~Edge()
  {
    delete vertex1;
    delete vertex2;
  }
};

class EdgeMathOperator: public Edge
{
private:

public:
  virtual double Calculate(const double v1, const double v2)=0;
  virtual ~EdgeMathOperator(){}
};

class EdgeAdd: public EdgeMathOperator
{
private:

public:
  double Calculate(const double v1, const double v2){return v1+v2;}
  EdgeAdd(){}
};

class EdgeSubtract: public EdgeMathOperator
{
private:

public:
  double Calculate(const double v1, const double v2){return v1-v2;}
  EdgeSubtract(){}
};

class EdgeMultiply: public EdgeMathOperator
{
private:

public:
  double Calculate(const double v1, const double v2){return v1*v2;}
  EdgeMultiply(){}
};

class EdgeDivide: public EdgeMathOperator
{
private:

public:
  double Calculate(const double v1, const double v2){return v1/v2;}
  EdgeDivide(){}
};

class EdgePower: public EdgeMathOperator
{
private:

public:
  double Calculate(const double v1, const double v2){return pow(v1, v2);}
  EdgePower(){}
};

class EdgeMathOperation: public Edge
{
private:
  EdgeMathOperator *mathOperator=nullptr;

  void SetOperator(const string &s)
  {
    if(s==ADD) mathOperator=new EdgeAdd;
    else if(s==SUBTRACT) mathOperator=new EdgeSubtract;
    else if(s==MULTIPLY) mathOperator=new EdgeMultiply;
    else if(s==DIVIDE) mathOperator=new EdgeDivide;
    else if(s==EXP) mathOperator=new EdgePower;
  }

  template<typename T, typename U>
  void CreateEdge(const string &s1, const string &s2, const string &o)
  {
    this->vertex1=new T(s1);
    this->vertex2=new U(s2);
    this->SetOperator(o);
  }
public:
  double result=NAN;
  EdgeMathOperation(){}
  ~EdgeMathOperation(){delete mathOperator;}
};

class EdgeVariableVariable: public EdgeMathOperation
{
private:

public:
};

class EdgeVariableConstant: public EdgeMathOperation
{
private:

public:
};

class EdgeVariableNumeric: public EdgeMathOperation
{
private:

public:
};

class EdgeConstantVariable: public EdgeMathOperation
{
private:

public:
};

class EdgeConstantConstant: public EdgeMathOperation
{
private:

public:
};

class EdgeConstantNumeric: public EdgeMathOperation
{
private:

public:
};

class EdgeNumericVariable: public EdgeMathOperation
{
private:

public:
};

class EdgeNumericConstant: public EdgeMathOperation
{
private:

public:
};

class EdgeNumericNumeric: public EdgeMathOperation
{
private:

public:
};

#endif
