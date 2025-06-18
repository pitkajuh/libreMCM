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
	cout<<"Calculating "<<vertex.mathOperator<<" "<<vertex.value1<<" "<<vertex.value2<<" "<<vertex.result<<'\n';
	cout<<"Calculating "<<vertex.mathOperator<<" "<<*vertex.value1<<" "<<*vertex.value2<<" "<<vertex.result<<'\n';
	vertex.Calculate();
	cout<<"Result is "<<*vertex.result<<'\n';
	// cout<<n<<" "<<*vertex.result<<'\n';
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
    for(Equation &equation: equations)
      {
	equation.Calculate();
      }
  }
};

#endif
