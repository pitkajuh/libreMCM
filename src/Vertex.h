#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include "MathOperator.h"
#include <iostream>
using std::cout;
using std::string;

class Vertex
{
public:
  Vertex(){};
  virtual ~Vertex(){};
  virtual double GetValue()=0;
  virtual void Calculate()=0;
};

struct VertexNew
{
public:
  bool value1Negative=0;
  bool value2Negative=0;
  MathOperator *mathOperator=nullptr;

  double *value1=nullptr;
  double *value2=nullptr;
  double *result=nullptr;

  VertexNew(){}
  ~VertexNew(){}
};

#endif
