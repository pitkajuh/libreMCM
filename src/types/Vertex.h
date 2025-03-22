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

  bool GetNegative(){return negative;}
  const string GetName(){return name;}
  double GetValue(){return value;}
  VertexValue(){};
  virtual VertexValue(){};
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

#endif
