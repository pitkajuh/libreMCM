#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::cout;

struct Vertex
{
private:
  string name;
  uint8_t id;
public:

  uint16_t n;
  uint16_t nx;
  vector<double> values;

  void PrintVertex()
  {
    std::cout<<name<<'\n';

    for(const double &i: values)
      {
	std::cout<<i<<'\n';
      }
    std::cout<<" "<<'\n';
  }

  const string& GetName() const
  {
    return name;
  }

  uint8_t GetId()
  {
    return id;
  }

  void AddValue(const double value)
  {
    values.emplace_back(value);
  }

  Vertex(){}
  Vertex(const uint16_t n1, const uint16_t nx1, const string name1, const uint8_t id1)
  {
    this->id=id1;
    this->n=n1;
    this->nx=nx1;
    this->name=name1;
    values.reserve(n1);
  }
  ~Vertex(){}
};

#endif
