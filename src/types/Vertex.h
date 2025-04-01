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
  virtual void Calculate()=0;
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
  // double GetValue(){cout<<"VertexValue GetValue"<<'\n'; return value;}
  virtual double GetValue(){return 0;};
  void Calculate(){cout<<"VertexValue Calculate"<<'\n';}
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
  // void Calculate(){cout<<"VertexNumeric Calculate"<<'\n';};
  double GetValue()
  {
    cout<<"VertexNumeric GetValue"<<'\n';
    return value;
  }
  VertexNumeric(const string &s){SetValue(stod(s));}
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
  void Calculate(){cout<<"VertexMultiValue Calculate"<<'\n';};
  VertexMultiValue(){}
  VertexMultiValue(const string &s){this->SetOperator(s);}
  ~VertexMultiValue()
  {
    // cout<<"~VertexMultiValue()"<<'\n';
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
    cout<<"VertexVertices Calculate"<<'\n';
    cout<<vertex1->GetValue()<<" "<<vertex2->GetValue()<<'\n';
    result=mathOperator->Calculate(vertex1->GetValue(), vertex2->GetValue());
    cout<<result<<'\n';
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

#endif
