#ifndef VERTEX_H
#define VERTEX_H

#include "MathOperator.h"
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

struct VertexNew
{
public:
  int8_t value1Negative=1;
  int8_t value2Negative=1;
  MathOperator *mathOperator=nullptr;

  double *value1=nullptr;
  double *value2=nullptr;
  double *result=nullptr;

  void Calculate()
  {
    result=new double(mathOperator->Calculate(*value1, *value2));
  }

  VertexNew(){}
  ~VertexNew(){}
};

#endif
