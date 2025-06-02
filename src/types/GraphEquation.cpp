#include "Vertex.h"
#include "Graph.h"
#include "../global/MathOperators.h"

template<typename T>
bool GraphEquation::IsInMap(const string &s, T &map){return map.count(s)>0;}

template<typename T>
void GraphEquation::AddToMap(Vertex *v, const string &s, T &map)
{
  if(!IsInMap<T>(s, map)) map[s]=v;
  else cout<<"AA "<<map[s]<<'\n';
}

template<typename T, typename U>
void GraphEquation::CreateVertexNumeric(const string &s1, const string &s2, const string &mathOperator, const uint8_t id, map<string, Vertex*> &map1, vector<Vertex*> &map2)
{
  VertexValue *vertex1=new VertexNumeric(s1);
  Vertex *vertex2=nullptr;
  cout<<"A "<<s1<<" "<<s2<<" "<<std::to_string(id)<<'\n';
  if(!IsInMap(s2, map1))
    {
      vertex2=new T(s2);
      AddToMap(vertex2, s2, map1);
    }
  else vertex2=map1[s2];

  VertexVertices *v=new U(vertex1, vertex2, mathOperator);
  map2.emplace_back(v);
}

template<typename T>
Vertex *GraphEquation::CreateVertex2(const string &s, map<string, Vertex*> &map)
{
  Vertex *v=nullptr;

  if(!IsInMap(s, map))
    {
      v=new T(s);
      AddToMap(v, s, map);
    }
  else v=map[s];
  return v;
}

void GraphEquation::SubstituteConstants(const SMap &constants_map)
{
}

template<typename T, typename U, typename L, typename H, typename A>
void GraphEquation::AddMath2(const string &s2, const string &mathOperator, const uint8_t id, U &map1, L &map2, const bool b, const H s, const A h)
{
  Vertex *v1=nullptr;

  if(b)
    {
      v1=new T(s2);
      map2.emplace_back(v1);
    }
  else v1=map2[s];

  VertexVertices *v=new VertexVertices(h, v1, mathOperator);
  map2.emplace_back(v);
}

template<typename T, typename U, typename L, typename H, typename A>
void GraphEquation::AddMath(const string &s2, const string &mathOperator, const uint8_t id, U &map1, L &map2, const bool b, const H s, const A h)
{
  Vertex *v1=nullptr;

  if(b)
    {
      v1=new T(s2);
      map2[s2]=v1;
    }
  else v1=map2[s];

  VertexVertices *v=new VertexVertices(h, v1, mathOperator);
  map1.emplace_back(v);
}

template<typename T, typename U>
void GraphEquation::CreateVertex(const string &s1, const string &s2, const string &mathOperator, const uint8_t id, vector<Vertex*> &map1, map<string, Vertex*> &map2, map<string, Vertex*> &map3)
{
  cout<<"Create ID="<<std::to_string(id)<<", "<<s1<<" "<<s2<<'\n';
  Vertex *vertex1=CreateVertex2<T>(s1, map2);
  Vertex *vertex2=CreateVertex2<U>(s2, map3);
  VertexVertices *v=new VertexVertices(vertex1, vertex2, mathOperator);
  cout<<s1<<" "<<s2<<" "<<"@"<<std::to_string(id)<<'\n';
  map1.emplace_back(v);
}

void GraphEquation::CreateMath(const string &s1, const string &s2, const string &mathOperator, const uint8_t id)
{
  if(vmap[stoi(s1.substr(1, s1.size()-1))]->GetValue()!=NAN)
    {
      VertexMultiValue *v1=new VertexMultiValue(mathOperator);
      Vertex *v=new VertexNumeric(v1->GetOperator(vmap[stoi(s1.substr(1, s1.size()-1))]->GetValue(), stod(s2)));
      vmap.emplace_back(v);
      delete v1;
    }
  else
    {
      Vertex *v1=new VertexNumeric(stod(s2));
      VertexVertices *v=new VertexVertices(vmap[stoi(s1.substr(1, s1.size()-1))], v1, mathOperator);
      vmap.emplace_back(v);
    }
}

void GraphEquation::CreateEdge(const string &s1, const string &s2, const string &mathOperator, const Bools &b1, const Bools &b2, const uint8_t id)
{
  cout<<" "<<'\n';
  cout<<s1<<" "<<s2<<'\n';

  if(b1.variable and b2.variable)
    {
      cout<<"b1.variable and b2.variable"<<'\n';
      CreateVertex<VertexVariable, VertexVariable>(s1, s2, mathOperator, id, vmap, variables, variables);
    }
  else if(b1.variable and b2.constant)
    {
      cout<<"if(b1.variable and b2"<<'\n';
      CreateVertex<VertexVariable, VertexConstant>(s1, s2, mathOperator, id, vmap, variables, constants);
    }
  else if(b1.variable and b2.numeric)
    {
      cout<<"if(b1.variable and b2"<<'\n';
      CreateVertexNumeric<VertexVariable, VertexVerticesNumeric2>(s2, s1, mathOperator, id, variables, vmap);
    }
  else if(b1.constant and b2.variable)
    {
      cout<<"b1.constant and b2.variable"<<'\n';
      CreateVertex<VertexConstant, VertexVariable>(s1, s2, mathOperator, id, vmap, constants, variables);
    }
  else if(b1.constant and b2.constant)
    {
      cout<<"b1.constant and b2.constant"<<'\n';
      CreateVertex<VertexConstant, VertexConstant>(s1, s2, mathOperator, id, vmap, constants, constants);
    }
  else if(b1.constant and b2.numeric)
    {
      cout<<"b1.constant and b2.numeric"<<'\n';
      CreateVertexNumeric<VertexConstant, VertexVerticesNumeric2>(s2, s1, mathOperator, id, constants, vmap);
    }
  else if(b1.numeric and b2.variable)
    {
      cout<<"b1.numeric and b2.variable"<<'\n';
      CreateVertexNumeric<VertexVariable, VertexVerticesNumeric1>(s1, s2, mathOperator, id, variables, vmap);
    }
  else if(b1.numeric and b2.constant)
    {
      cout<<"b1.numeric and b2.constant"<<'\n';
      CreateVertexNumeric<VertexConstant, VertexVerticesNumeric1>(s1, s2, mathOperator, id, constants, vmap);
    }
  else if(b1.numeric and b2.numeric)
    {
      // Result can be calculated in advance, so the equation template can
      // be simplified and performance of the calculation increased.
      cout<<"b1.numeric and b2.numeric "<<s1<<" "<<s2<<'\n';
      VertexValue *vertex1=new VertexNumeric(s1);
      VertexValue *vertex2=new VertexNumeric(s2);
      VertexVertices *v=new VertexVertices(vertex1, vertex2, mathOperator);
      v->Calculate();
      VertexValue *calculated=new VertexNumeric(v->GetValue());

      // vmap["@"+std::to_string(id)]=calculated;
      vmap.emplace_back(calculated);
      delete vertex1;
      delete vertex2;
      delete v;
      cout<<calculated<<'\n';
    }
  else if(b1.math and b2.math)
    {
      cout<<"b1.math and b2.math "<<'\n';
      VertexVertices *v1=new VertexVertices(vmap[stoi(s1.substr(1, s1.size()-1))], vmap[stoi(s2.substr(1, s1.size()-1))], mathOperator);
      // vmap["@"+std::to_string(id)]=v1;
      vmap.emplace_back(v1);
    }
  else if(b1.math and b2.constant)
    {
      cout<<"b1.math and b2.constant"<<'\n';
      AddMath<VertexConstant, vector<Vertex*>, map<string, Vertex*>, string, Vertex*>(s2, mathOperator, id, vmap, constants, !IsInMap(s2, constants), s2, vmap[stoi(s1.substr(1, s1.size()-1))]);
    }
  else if(b1.math and b2.variable)
    {
      cout<<"b1.math and b2.variable"<<'\n';
      AddMath<VertexVariable, vector<Vertex*>, map<string, Vertex*>, string, Vertex*>(s2, mathOperator, id, vmap, variables, !IsInMap(s2, variables), s2, vmap[stoi(s1.substr(1, s1.size()-1))]);
    }
  else if(b1.numeric and b2.math)
    {
      cout<<"b1.numeric and b2.math and vmap[s2]->GetValue()!=NAN"<<'\n';
      // Result can be calculated in advance, so the equation template can
      // be simplified and performance of the calculation increased.
      CreateMath(s2, s1, mathOperator, id);
    }
  else if(b2.math and b1.constant)
    {
      cout<<"b2.math and b1.constant "<<s1<<" "<<s2<<" "<<s2.substr(1, s2.size()-1)<<'\n';

      const int8_t id1=stoi(s2.substr(1, s2.size()-1));
      const int8_t id2=constants.size();

      AddMath2<VertexConstant, map<string, Vertex*>, vector<Vertex*>, int8_t, Vertex*>(s2, mathOperator, id, constants, vmap, id2<id1, id1, constants[s1]);
    }
  else if(b2.math and b1.variable)
    {
      cout<<"b2.math and b1.variable"<<'\n';

      const int8_t id1=stoi(s2.substr(1, s2.size()-1));
      const int8_t id2=vmap.size();

      AddMath2<VertexConstant, map<string, Vertex*>, vector<Vertex*>, uint8_t, Vertex*>(s2, mathOperator, id, variables, vmap, id2<id1, id1, variables[s1]);
    }
  else if(b2.numeric and b1.math)
    {
      cout<<"b2.numeric and b1.math and vmap[s1]->GetValue()!=NAN"<<" "<<s1<<" "<<s2<<'\n';
      // Result can be calculated in advance, so the equation template can
      // be simplified and performance of the calculation increased.
      CreateMath(s1, s2, mathOperator, id);
    }
  else if(!b1.variable and !b1.constant and !b1.numeric and !b1.math)
    {
      throw std::invalid_argument("Value \""+s1+"\" is not a constant, variable or numeric value.");
    }
  else
    {
      throw std::invalid_argument("Value \""+s2+"\" is not a constant, variable or numeric value.");
    }
}

void GraphEquationSingle::CreateVertex(const Bools &b, const string &e)
{
  if(b.variable) vertex=new VertexVariable(e);
  else if(b.constant) vertex=new VertexConstant(e);
  else vertex=new VertexNumeric(e);
}

GraphEquationSingle::GraphEquationSingle(const Bools &b, const string &e)
{
  this->CreateVertex(b, e);
}

GraphEquationSingle::~GraphEquationSingle(){delete vertex;}
