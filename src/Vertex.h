#ifndef VERTEX_H
#define VERTEX_H

struct Vertex
{
public:
  uint16_t n;
  uint16_t nx;
  double *values=nullptr;

  Vertex(){}
  Vertex(const uint16_t n1, const uint16_t nx1)
  {
    this->n=n1;
    this->nx=nx1;
    values=new double[n1];
  }
  ~Vertex(){delete [] values;}
};

#endif
