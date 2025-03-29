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

#include <string>
#include <vector>
#include <cstdint>

using std::string;
using std::vector;
#include <iostream>
using std::cout;

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

// class VertexNumeric: public VertexValue
// {
// private:
// public:
//   VertexNumeric(const string &s){SetName(s);}
//   VertexNumeric(){}
// };

// class VertexVariable: public VertexValue
// {
// private:
// public:
//   VertexVariable(const string &s){SetName(s);}
//   VertexVariable(){}
// };

class VertexMathOperator: public Vertex
{
public:
  virtual double Calculate(const double v1, const double v2)=0;
  ~VertexMathOperator(){}
};

// class VertexAdd: public VertexMathOperator
// {
// private:

// public:
//   double Calculate(const double v1, const double v2){return v1+v2;}
//   VertexAdd(){}
// };

// class VertexSubtract: public VertexMathOperator
// {
// private:

// public:
//   double Calculate(const double v1, const double v2){return v1-v2;}
//   VertexSubtract(){}
// };

class VertexMultiply: public VertexMathOperator
{
public:
  double Calculate(const double v1, const double v2){return v1*v2;}
  VertexMultiply(){}
};

// class VertexDivide: public VertexMathOperator
// {
// private:

// public:
//   double Calculate(const double v1, const double v2){return v1/v2;}
//   VertexDivide(){}
// };

// class VertexPower: public VertexMathOperator
// {
// private:

// public:
//   double Calculate(const double v1, const double v2){return pow(v1, v2);}
//   VertexPower(){}
// };

class VertexMultiValue: public Vertex
{
protected:
  VertexMathOperator *mathOperator=nullptr;
public:
  VertexMultiValue(){}
  VertexMultiValue(const string &s)
  {
    // if(s==ADD) mathOperator=new VertexAdd;
    // else if(s==SUBTRACT) mathOperator=new VertexSubtract;
    if(s==MULTIPLY) mathOperator=new VertexMultiply;
    // else if(s==DIVIDE) mathOperator=new VertexDivide;
    // else if(s==EXP) mathOperator=new VertexPower;
  }
  ~VertexMultiValue(){delete mathOperator;}
};

#endif
