#include "Vertex.h"
#include "Graph.h"

bool GraphEquation::IsInMap(const string &s, map<string, Vertex*> &map){return map.count(s)>0;}

void GraphEquation::AddToMap(Vertex *v, const string &s, map<string, Vertex*> &map)
{
  if(!IsInMap(s, map)) map[s]=v;
  else cout<<"AA "<<map[s]<<'\n';
}

template<typename T, typename U>
void GraphEquation::CreateVertexNumeric(const string &s1, const string &s2, const string &mathOperator, const uint8_t id, map<string, Vertex*> &map1, map<string, Vertex*> &map2)
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
  map2["@"+std::to_string(id)]=v;
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
  for(auto &[name, equation]:vmap)
    {
      cout<<name<<" "<<equation<<'\n';
    }
}

template<typename T>
void GraphEquation::AddMath(const string &s1, const string &s2, const string &mathOperator, const uint8_t id, map<string, Vertex*> &map1, map<string, Vertex*> &map2)
{
  Vertex *v1=nullptr;

  if(!IsInMap(s2, map2))
    {
      v1=new T(s2);
      map2[s2]=v1;
    }
  else v1=map2[s2];

  VertexVertices *v=new VertexVertices(map1[s1], v1, mathOperator);
  map1["@"+std::to_string(id)]=v;
}

template<typename T, typename U>
void GraphEquation::CreateVertex(const string &s1, const string &s2, const string &mathOperator, const uint8_t id, map<string, Vertex*> &map1, map<string, Vertex*> &map2, map<string, Vertex*> &map3)
{
  cout<<"Create ID="<<std::to_string(id)<<", "<<s1<<" "<<s2<<'\n';
  Vertex *vertex1=CreateVertex2<T>(s1, map2);
  Vertex *vertex2=CreateVertex2<U>(s2, map3);
  VertexVertices *v=new VertexVertices(vertex1, vertex2, mathOperator);
  cout<<s1<<" "<<s2<<" "<<"@"<<std::to_string(id)<<'\n';

  map1["@"+std::to_string(id)]=v;
  cout<<vertex1<<" "<<vertex2<<'\n';
  cout<<"Created"<<'\n';
}

void GraphEquation::CreateMath(const string &s1, const string &s2, const string &mathOperator, const uint8_t id)
{
  cout<<"vmap[s1]->GetValue()!=NAN "<<s1<<'\n';
  if(vmap[s1]->GetValue()!=NAN)
    {
      VertexMultiValue *v1=new VertexMultiValue(mathOperator);
      Vertex *v=new VertexNumeric(v1->GetOperator(vmap[s1]->GetValue(), std::stod(s2)));
      // cout<<"vmap[s1].GetValue()!=NAN "<<s2<<" "<<vmap[s1]->GetValue()<<" "<<v->GetValue()<<'\n';
      vmap["@"+std::to_string(id)]=v;
      delete v1;
    }
  else
    {
      cout<<"else"<<'\n';
      Vertex *v1=new VertexNumeric(std::stod(s2));
      VertexVertices *v=new VertexVertices(vmap[s1], v1, mathOperator);
      vmap["@"+std::to_string(id)]=v;
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

      vmap["@"+std::to_string(id)]=calculated;
      delete vertex1;
      delete vertex2;
      delete v;
      cout<<calculated<<'\n';
    }
  else if(b1.math and b2.math)
    {
      cout<<"b1.math and b2.math "<<'\n';
      VertexVertices *v1=new VertexVertices(vmap[s1], vmap[s2], mathOperator);
      vmap["@"+std::to_string(id)]=v1;
    }
  else if(b1.math and b2.constant)
    {
      cout<<"b1.math and b2.constant"<<'\n';
      AddMath<VertexConstant>(s1, s2, mathOperator, id, vmap, constants);
    }
  else if(b1.math and b2.variable)
    {
      cout<<"b1.math and b2.variable"<<'\n';
      AddMath<VertexVariable>(s1, s2, mathOperator, id, vmap, variables);
    }
  // else if(b1.numeric and b2.math and vmap[s2]->GetValue()!=NAN)
  else if(b1.numeric and b2.math)
    {
      cout<<"b1.numeric and b2.math and vmap[s2]->GetValue()!=NAN"<<'\n';
      // Result can be calculated in advance, so the equation template can
      // be simplified and performance of the calculation increased.
      CreateMath(s2, s1, mathOperator, id);

      // VertexMultiValue *v1=new VertexMultiValue(mathOperator);
      // Vertex *v=new VertexNumeric(v1->GetOperator(std::stod(s1), vmap[s2]->GetValue()));
      // cout<<"vmap[s1].GetValue()!=NAN "<<s1<<" "<<vmap[s2]->GetValue()<<" "<<v->GetValue()<<'\n';
      // vmap["@"+std::to_string(id)]=v;
      // delete v1;
    }
  else if(b2.math and b1.constant)
    {
      cout<<"b2.math and b1.constant"<<'\n';
      AddMath<VertexConstant>(s2, s1, mathOperator, id, constants, vmap);
    }
  else if(b2.math and b1.variable)
    {
      cout<<"b2.math and b1.variable"<<'\n';
      AddMath<VertexConstant>(s2, s1, mathOperator, id, variables, vmap);
    }
  // else if(b2.numeric and b1.math and vmap[s1]->GetValue()!=NAN)
  else if(b2.numeric and b1.math)
    {
      cout<<"b2.numeric and b1.math and vmap[s1]->GetValue()!=NAN"<<" "<<s1<<" "<<s2<<'\n';
      // Result can be calculated in advance, so the equation template can
      // be simplified and performance of the calculation increased.
      CreateMath(s1, s2, mathOperator, id);


      // VertexMultiValue *v1=new VertexMultiValue(mathOperator);
      // Vertex *v=new VertexNumeric(v1->GetOperator(vmap[s1]->GetValue(), std::stod(s2)));
      // cout<<"vmap[s1].GetValue()!=NAN "<<s2<<" "<<vmap[s1]->GetValue()<<" "<<v->GetValue()<<'\n';
      // vmap["@"+std::to_string(id)]=v;
      // delete v1;
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
  if(b.variable){vertex=new VertexVariable(e);}
  else if(b.constant){vertex=new VertexConstant(e);}
  else{vertex=new VertexNumeric(e);}
}

GraphEquationSingle::GraphEquationSingle(const Bools &b, const string &e)
{
  this->CreateVertex(b, e);
}

GraphEquationSingle::~GraphEquationSingle(){delete vertex;}
