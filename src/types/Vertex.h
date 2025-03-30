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
#include <iostream>
using std::cout;

class Edge;

class Vertex
{
public:
  Vertex(){};
  virtual ~Vertex(){};
  virtual double GetValue()=0;
};

class VertexValue: public Vertex
{
protected:
  bool negative=0;
  string name="";
  double value=NAN;
public:
  // double GetValue(){return value;}

  void SetName(const string &s)
  {
    name=s;

    if(s[0]=='-')
      {
	negative=1;
	name=name.substr(1, name.size());
      }
  }

  void SetValue(const double v)
  {
    value=v;

    if(negative) value=-1*value;
  }

  const bool GetNegative(){return negative;}
  const string GetName(){return name;}
  double GetValue(){return value;}
  VertexValue(){};
  ~VertexValue(){};
};

class VertexConstant: public VertexValue
{
private:
public:
  // double GetValue(){return value;}
  VertexConstant(const string &s){SetName(s);}
  VertexConstant(){}
  ~VertexConstant(){}
};

class VertexNumeric: public VertexValue
{
private:
public:
  // double GetValue(){return value;}
  VertexNumeric(const string &s){SetName(s);}
  VertexNumeric(){}
  ~VertexNumeric(){}
};

class VertexVariable: public VertexValue
{
private:
public:
  // double GetValue(){return value;}
  VertexVariable(const string &s){SetName(s);}
  VertexVariable(){}
  ~VertexVariable(){}
};

class VertexMultiValue: public Vertex
{
protected:
  MathOperator *mathOperator=nullptr;
  double result;

  void SetOperator(const string &s)
  {
    if(s==ADD) mathOperator=new Add;
    else if(s==SUBTRACT) mathOperator=new Sub;
    else if(s==MULTIPLY) mathOperator=new Mul;
    else if(s==DIVIDE) mathOperator=new Div;
    else if(s==EXP) mathOperator=new Exp;
  }
public:
  double GetValue(){return result;}
  virtual void Calculate()=0;
  VertexMultiValue(){}
  VertexMultiValue(const string &s){this->SetOperator(s);}
  ~VertexMultiValue()
  {
    cout<<"~VertexMultiValue()"<<'\n';
    delete mathOperator;
  }
};

class VertexVertices: public VertexMultiValue
{
protected:
  Vertex *vertex1=nullptr;
  Vertex *vertex2=nullptr;
public:
  void Calculate()
  {
    // result=mathOperator->Calculate(vertex1->value, vertex2->value);
  }
  VertexVertices(){}
  VertexVertices(Vertex *vertex1, Vertex *vertex2, const string &s)
  {
    this->vertex1=vertex1;
    this->vertex2=vertex2;
    this->SetOperator(s);
  }
  ~VertexVertices(){}
};

// class VertexMathVertex: public VertexMultiValue
// {
// protected:
//   Edge *edge1=nullptr;
// public:
//   VertexMathVertex(){}
//   VertexMathVertex(Edge *edge1){this->edge1=edge1;}
//   ~VertexMathVertex(){}
// };

// class VertexVertexEdge: public VertexMathVertex
// {
// protected:
//   Vertex *vertex=nullptr;
// public:
//   VertexVertexEdge(){}
//   ~VertexVertexEdge(){}
// };

// class VertexMathVertex2: public VertexMathVertex
// {
// protected:
//   Edge *edge2=nullptr;
// public:
//   VertexMathVertex2(){}
//   VertexMathVertex2(Edge *edge1, Edge *edge2)
//   {
//     this->edge1=edge1;
//     this->edge2=edge2;
//   }
//   ~VertexMathVertex2(){}
// };

#endif
