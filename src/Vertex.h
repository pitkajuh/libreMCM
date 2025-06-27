#ifndef VERTEX_H
#define VERTEX_H

#include "MathOperator.h"

struct Vertex
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
    *result=mathOperator->Calculate(*value1, *value2);
    cout<<*value1<<mathOperator->GetOp()<<*value2<<"="<<*result<<'\n';
  }

  Vertex(){}
  ~Vertex(){}
};

#endif
