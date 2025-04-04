/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <cstdint>
#include "Edge.h"
#include "Vertex.h"
#include "Bools.h"
#include <map>

using std::map;
using std::string;
using std::vector;
#include <iostream>
using std::cout;

class Graph
{
public:
  Graph(){}
  virtual ~Graph(){}
};

class GraphEquation: public Graph
{
protected:
  map<string, Vertex*> vmap;
  map<string, Vertex*> constants;
  map<string, Vertex*> variables;

  bool IsInMap(const string &s);
  void AddToMap(Vertex *v, const string &s);

  template<typename T, typename U>
  void CreateVertexNumeric(const string &s1, const string &s2, const string &mathOperator, const uint8_t id);

  template<typename T>
  Vertex *CreateVertex2(const string &s1);

  template<typename T, typename U>
  void CreateVertex(const string &s1, const string &s2, const string &mathOperator, const uint8_t id);

public:
  void SubstituteConstants(const SMap &constants_map);
  void CreateEdge(const string &s1, const string &s2, const string &mathOperator, const Bools &b1, const Bools &b2, const uint8_t id);
  GraphEquation(){}
  ~GraphEquation()
  {
    cout<<"~GraphEquation "<<'\n';
    for(auto &[i1, i2]: vmap)
      delete i2;
    for(auto &[i1, i2]: constants)
      delete i2;
    for(auto &[i1, i2]: variables)
      delete i2;
  }
};

class GraphEquationSingle: public GraphEquation
{
protected:
  VertexValue *vertex=nullptr;

  void CreateVertex(const Bools &b, const string &e);
public:
  GraphEquationSingle(){}
  GraphEquationSingle(const Bools &b, const string &e);
  ~GraphEquationSingle();
};

#endif
