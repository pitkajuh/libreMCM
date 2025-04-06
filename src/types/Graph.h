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

  bool IsInMap(const string &s, map<string, Vertex*> &map);
  void AddToMap(Vertex *v, const string &s, map<string, Vertex*> &map);

  template<typename T, typename U>
  void CreateVertexNumeric(const string &s1, const string &s2, const string &mathOperator, const uint8_t id, map<string, Vertex*> &map);

  template<typename T>
  Vertex *CreateVertex2(const string &s, map<string, Vertex*> &map);

  template<typename T, typename U>
  void CreateVertex(const string &s1, const string &s2, const string &mathOperator, const uint8_t id, map<string, Vertex*> &map1, map<string, Vertex*> &map2, map<string, Vertex*> &map3);

  template<typename T>
  void AddMath(const string &s1, const string &s2, const string &mathOperator, const uint8_t id, map<string, Vertex*> &map1, map<string, Vertex*> &map2);

  void CreateMath(const string &s1, const string &s2, const string &mathOperator, const uint8_t id);

public:
  void SubstituteConstants(const SMap &constants_map);
  void CreateEdge(const string &s1, const string &s2, const string &mathOperator, const Bools &b1, const Bools &b2, const uint8_t id);
  GraphEquation(){}
  ~GraphEquation()
  {
    cout<<"~GraphEquation "<<vmap.size()<<" "<<constants.size()<<" "<<variables.size()<<'\n';
    for(auto &[i1, i2]: vmap)
      {
	cout<<"delete "<<i1<<" "<<i2<<'\n';
	delete i2;
      }
    cout<<" "<<'\n';
    for(auto &[i1, i2]: constants)
      {
	cout<<"delete "<<i1<<" "<<i2<<'\n';
	delete i2;
      }
    cout<<" "<<'\n';
    for(auto &[i1, i2]: variables)
      {
	cout<<"delete "<<i1<<" "<<i2<<'\n';
	delete i2;
      }
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
