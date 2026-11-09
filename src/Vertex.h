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
  uint16_t id;
  vector<double> values;
public:

  uint16_t n;
  uint16_t nx;

  void PrintVertex()
  {
    std::cout<<name<<'\n';

    for(const double &i: values)
      {
	std::cout<<i<<'\n';
      }
    std::cout<<" "<<'\n';
  }

  vector<double>& GetValues()
  {
    return values;
  }

  double GetLastValue() const
  {
    return values.back();
  }

  const string& GetName() const
  {
    return name;
  }

  uint8_t GetId() const
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
