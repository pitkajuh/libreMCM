#ifndef GRAPHEQUATION_H
#define GRAPHEQUATION_H

#include <cstdint>
#include "Vertex.h"

struct Equation
{
public:
  uint16_t id;
  vector<VertexNew> vertices;

  void Calculate()
  {
    int n=0;
    for(VertexNew &vertex: vertices)
      {
	vertex.Calculate();
	cout<<n<<" "<<*vertex.result<<'\n';
	n++;
      }
  }
};

struct Equations
{
public:
  vector<Equation> equations;

  void Calculate()
  {
    cout<<"Calculate"<<'\n';
    for(Equation &equation: equations)
      {
	equation.Calculate();
      }
  }
};

#endif
