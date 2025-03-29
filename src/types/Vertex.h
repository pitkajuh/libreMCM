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

#include <iostream>
using std::cout;

class Edge;

class Vertex
{
public:
  Vertex(){};
  virtual ~Vertex(){};
};

class VertexValue: public Vertex
{
protected:
  bool negative=0;
  string name="";
  double value=NAN;
public:
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
  VertexConstant(const string &s){SetName(s);}
  VertexConstant(){}
  ~VertexConstant(){}
};

class VertexNumeric: public VertexValue
{
private:
public:
  VertexNumeric(const string &s){SetName(s);}
  VertexNumeric(){}
  ~VertexNumeric(){}
};

class VertexVariable: public VertexValue
{
private:
public:
  VertexVariable(const string &s){SetName(s);}
  VertexVariable(){}
  ~VertexVariable(){}
};

class VertexMathOperator: public Vertex
{
public:
  virtual double Calculate(const double v1, const double v2)=0;
  ~VertexMathOperator(){}
};

class VertexAdd: public VertexMathOperator
{
public:
  double Calculate(const double v1, const double v2){return v1+v2;}
  VertexAdd(){}
  ~VertexAdd(){}
};

class VertexSubtract: public VertexMathOperator
{
public:
  double Calculate(const double v1, const double v2){return v1-v2;}
  VertexSubtract(){}
  ~VertexSubtract(){}
};

class VertexMultiply: public VertexMathOperator
{
public:
  double Calculate(const double v1, const double v2){return v1*v2;}
  VertexMultiply(){}
  ~VertexMultiply(){}
};

class VertexDivide: public VertexMathOperator
{
public:
  double Calculate(const double v1, const double v2){return v1/v2;}
  VertexDivide(){}
  ~VertexDivide(){}
};

class VertexPower: public VertexMathOperator
{
public:
  double Calculate(const double v1, const double v2){return pow(v1, v2);}
  VertexPower(){}
  ~VertexPower(){}
};

class VertexMultiValue: public Vertex
{
protected:
  VertexMathOperator *mathOperator=nullptr;
public:
  VertexMultiValue(){}
  VertexMultiValue(const string &s)
  {
    if(s==ADD) mathOperator=new VertexAdd;
    else if(s==SUBTRACT) mathOperator=new VertexSubtract;
    else if(s==MULTIPLY) mathOperator=new VertexMultiply;
    else if(s==DIVIDE) mathOperator=new VertexDivide;
    else if(s==EXP) mathOperator=new VertexPower;
  }
  ~VertexMultiValue()
  {
    cout<<"~VertexMultiValue()"<<'\n';
    delete mathOperator;
  }
};

class VertexMathVertex: public VertexMultiValue
{
protected:
  Edge *edge1=nullptr;
public:
  VertexMathVertex(){}
  VertexMathVertex(Edge *edge1){this->edge1=edge1;}
  ~VertexMathVertex(){}
};

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
//   ~VertexMathVertex(){}
// };

#endif
