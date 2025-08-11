#ifndef VERTEX_H
#define VERTEX_H

struct Vertex
{
public:
  uint16_t n;
  uint16_t nx;
  double *values=nullptr;

  Vertex(){}
  Vertex(const uint16_t n, const uint16_t nx)
  {
    this->n=n;
    this->nx=nx;
    values=new double[n];
  }
  ~Vertex(){delete [] values;}
};

#endif
