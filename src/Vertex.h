#ifndef VERTEX_H
#define VERTEX_H

struct Vertex
{
private:
  string name;
public:

  uint16_t n;
  uint16_t nx;
  vector<double> values;

  string& GetName()
  {
    return name;
  }

  void AddValue(const double value)
  {
    values.emplace_back(value);
  }

  Vertex(){}
  Vertex(const uint16_t n1, const uint16_t nx1)
  {
    this->n=n1;
    this->nx=nx1;
    values.reserve(n1);
  }
  ~Vertex()
  {
  }
};

#endif
