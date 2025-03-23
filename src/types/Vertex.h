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
private:

public:

};

class VertexValue: public Vertex
{
private:
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
  virtual ~VertexValue(){};
};

class VertexConstant: public VertexValue
{
private:
public:
  VertexConstant(const string &s){SetName(s);}
  VertexConstant(){}
};

class VertexNumeric: public VertexValue
{
private:
public:
  VertexNumeric(const string &s){SetName(s);}
  VertexNumeric(){}
};

class VertexVariable: public VertexValue
{
private:
public:
  VertexVariable(const string &s){SetName(s);}
  VertexVariable(){}
};

class VertexMathOperator: public Vertex
{
private:

public:
  virtual double Calculate(const double v1, const double v2)=0;
  virtual ~VertexMathOperator(){}
};

class VertexAdd: public VertexMathOperator
{
private:

public:
  double Calculate(const double v1, const double v2){return v1+v2;}
  VertexAdd(){}
};

class VertexSubtract: public VertexMathOperator
{
private:

public:
  double Calculate(const double v1, const double v2){return v1-v2;}
  VertexSubtract(){}
};

class VertexMultiply: public VertexMathOperator
{
private:

public:
  double Calculate(const double v1, const double v2){return v1*v2;}
  VertexMultiply(){}
};

class VertexDivide: public VertexMathOperator
{
private:

public:
  double Calculate(const double v1, const double v2){return v1/v2;}
  VertexDivide(){}
};

class VertexPower: public VertexMathOperator
{
private:

public:
  double Calculate(const double v1, const double v2){return pow(v1, v2);}
  VertexPower(){}
};









class VertexMultiValue: public Vertex
{
protected:
  VertexValue *v1=nullptr;
  VertexValue *v2=nullptr;
  VertexMathOperator *mathOperator=nullptr;

  void SetOperator(const string &s)
  {
    if(s==ADD) mathOperator=new VertexAdd;
    else if(s==SUBTRACT) mathOperator=new VertexSubtract;
    else if(s==MULTIPLY) mathOperator=new VertexMultiply;
    else if(s==DIVIDE) mathOperator=new VertexDivide;
    else if(s==EXP) mathOperator=new VertexPower;
  }

public:

  void SetVertices(VertexValue *v1, VertexValue *v2)
  {
    this->v1=v1;
    this->v2=v2;
  }
  VertexMultiValue(){}
  ~VertexMultiValue()
  {
    delete v1;
    delete v2;
  }
};

class VertexVariableVariable: public VertexMultiValue
{
private:

public:
};

class VertexVariableConstant: public VertexMultiValue
{
private:

public:
};

class VertexVariableNumeric: public VertexMultiValue
{
private:

public:
};

class VertexConstantVariable: public VertexMultiValue
{
private:

public:
};

class VertexConstantConstant: public VertexMultiValue
{
private:

public:
};

class VertexConstantNumeric: public VertexMultiValue
{
private:

public:
};

class VertexNumericVariable: public VertexMultiValue
{
private:

public:
};

class VertexNumericConstant: public VertexMultiValue
{
private:

public:
};

class VertexNumericNumeric: public VertexMultiValue
{
private:

public:
};

#endif
