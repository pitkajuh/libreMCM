/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef VERTEX_H
#define VERTEX_H

#include "MathOperator.h"
#include "mathconst.h"
#include <iostream>
using std::cout;

class Vertex
{
public:
  Vertex(){};
  virtual ~Vertex(){};
  virtual double GetValue()=0;
  virtual void Calculate()=0;
};

class VertexValue: public Vertex
{
protected:
  bool negative=0;
  string name="";
  double value=NAN;
public:
  void SetName(const string &s);
  void SetValue(const double v);
  void Calculate();
  const bool GetNegative();
  const string GetName();
  virtual double GetValue(){return value;};
  VertexValue(VertexValue &v)
  {
    this->negative=v.GetNegative();
    this->name=v.name;
    this->value=v.value;
  }
  VertexValue &operator=(VertexValue &v)
  {
    if(this==&v) return *this;

    this->negative=v.GetNegative();
    this->name=v.name;
    this->value=v.value;
  }
  VertexValue(VertexValue &&v) noexcept
  {
    this->negative=v.GetNegative();
    this->name=v.name;
    this->value=v.value;
  }
  VertexValue &operator=(VertexValue &&v) noexcept
  {
    if(this==&v) return *this;

    this->negative=v.GetNegative();
    this->name=v.name;
    this->value=v.value;
  }
  VertexValue(){};
  ~VertexValue(){};
};

class VertexConstant: public VertexValue
{
public:
  double GetValue();
  VertexConstant(const string &s);
  VertexConstant(){}
  ~VertexConstant(){}
};

class VertexNumeric: public VertexValue
{
public:
  double GetValue();
  VertexNumeric(const string &s);
  VertexNumeric(const double s);
  VertexNumeric(){}
  ~VertexNumeric(){}
};

class VertexVariable: public VertexValue
{
public:
  double GetValue();
  VertexVariable(const string &s);
  VertexVariable(){}
  ~VertexVariable(){}
};

class VertexMultiValue: public Vertex
{
protected:
  MathOperator *mathOperator=nullptr;
  double result;
  void SetOperator(const string &s);
public:
  double GetOperator(const double d1, const double d2);
  double GetValue();
  void Calculate();
  VertexMultiValue(){}
  VertexMultiValue(const string &s);
  ~VertexMultiValue();
};

class VertexVertices: public VertexMultiValue
{
protected:
  Vertex *vertex1=nullptr;
  Vertex *vertex2=nullptr;
public:
  void Calculate();
  VertexVertices(){}
  VertexVertices(Vertex *vertex1, Vertex *vertex2, const string &s);
  ~VertexVertices(){}
};

class VertexVerticesNumeric1: public VertexVertices
{
public:
  VertexVerticesNumeric1(){}
  VertexVerticesNumeric1(Vertex *vertex1, Vertex *vertex2, const string &s);
  ~VertexVerticesNumeric1();
};

class VertexVerticesNumeric2: public VertexVertices
{
public:
  VertexVerticesNumeric2(){}
  VertexVerticesNumeric2(Vertex *vertex1, Vertex *vertex2, const string &s);
  ~VertexVerticesNumeric2();
};

#endif
