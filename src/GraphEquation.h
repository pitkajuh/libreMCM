#ifndef GRAPHEQUATION_H
#define GRAPHEQUATION_H

#include "Graph.h"
#include <string>
#include <vector>
#include <cstdint>
#include "Edge.h"
#include "Vertex.h"
#include "Bools.h"
#include <map>
#include <unordered_map>
#include "MathOperator.h"
#include "Edge.h"

using std::unordered_map;
using std::map;
using std::string;
using std::vector;
#include <iostream>
using std::cout;

class GraphEquationNew: public Graph
{
public:
  Edge *edge=nullptr;
};

class GraphEquation: public Graph
{
protected:
  vector<Vertex*> vmap;
  map<string, Vertex*> constants;
  map<string, Vertex*> variables;

  template<typename T>
  bool IsInMap(const string &s, T &map);

  template<typename T>
  void AddToMap(Vertex *v, const string &s, T &map);

  template<typename T, typename U>
  void CreateVertexNumeric(const string &s1, const string &s2, const string &mathOperator, const uint8_t id, map<string, Vertex*> &map1, vector<Vertex*> &map2);

  template<typename T>
  Vertex *CreateVertex2(const string &s, map<string, Vertex*> &map);

  template<typename T, typename U>
  void CreateVertex(const string &s1, const string &s2, const string &mathOperator, const uint8_t id, vector<Vertex*> &map1, map<string, Vertex*> &map2, map<string, Vertex*> &map3);

  template<typename T, typename U, typename L, typename H, typename A>
  void AddMath(const string &s2, const string &mathOperator, const uint8_t id, U &map1, L &map2, const bool b, const H s, const A h);

  template<typename T, typename U, typename L, typename H, typename A>
  void AddMath2(const string &s2, const string &mathOperator, const uint8_t id, U &map1, L &map2, const bool b, const H s, const A h);

  void CreateMath(const string &s1, const string &s2, const string &mathOperator, const uint8_t id);

public:
  void SubstituteConstants(const SMap &constants_map);
  void CreateEdge(const string &s1, const string &s2, const string &mathOperator, const Bools &b1, const Bools &b2, const uint8_t id);
  GraphEquation(){}
  ~GraphEquation()
  {
    // cout<<"~GraphEquation "<<vmap.size()<<" "<<constants.size()<<" "<<variables.size()<<'\n';
    // cout<<"delete math"<<'\n';

    for(auto &i2: vmap)
      {
	// cout<<"delete "<<" "<<i2<<'\n';
	delete i2;
      }

    // cout<<" "<<'\n';
    // cout<<"delete constants"<<'\n';
    for(auto &[i1, i2]: constants)
      {
	// cout<<"delete "<<i1<<" "<<i2<<'\n';
	delete i2;
      }
    // cout<<" "<<'\n';
    // cout<<"delete variables "<<'\n';
    for(auto &[i1, i2]: variables)
      {
	// cout<<"delete "<<i1<<" "<<i2<<'\n';
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
