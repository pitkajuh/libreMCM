#include "Vertex.h"
#include "Graph.h"

bool GraphEquation::IsInMap(const string &s){return vmap.count(s)>0;}

void GraphEquation::AddToMap(Vertex *v, const string &s)
{
  if(!IsInMap(s)) vmap[s]=v;
  else cout<<"AA "<<vmap[s]<<'\n';
}

template<typename T, typename U>
void GraphEquation::CreateVertexNumeric(const string &s1, const string &s2, const string &mathOperator, const uint8_t id)
{
  VertexValue *vertex1=new VertexNumeric(s1);
  Vertex *vertex2=nullptr;

  if(!IsInMap(s2))
    {
      vertex2=new T(s2);
      AddToMap(vertex2, s2);
    }
  else vertex2=vmap[s2];

  VertexVertices *v=new U(vertex1, vertex2, mathOperator);
  vmap["@"+std::to_string(id)]=v;
}

template<typename T, typename U, typename L, typename I>
void GraphEquation::CreateVertex(const string &s1, const string &s2, const string &mathOperator, const uint8_t id)
{
  cout<<"Create ID="<<std::to_string(id)<<", "<<s1<<" "<<s2<<'\n';
  Vertex *vertex1=nullptr;
  Vertex *vertex2=nullptr;

  if(!IsInMap(s1))
    {
      vertex1=new T(s1);
      AddToMap(vertex1, s1);
    }
  else vertex1=vmap[s1];

  if(!IsInMap(s2))
    {
      vertex2=new T(s2);
      AddToMap(vertex2, s2);
    }
  else vertex2=vmap[s2];

  VertexVertices *v=new VertexVertices(vertex1, vertex2, mathOperator);
  cout<<s1<<" "<<s2<<" "<<"@"<<std::to_string(id)<<'\n';

  vmap["@"+std::to_string(id)]=v;
  cout<<vertex1<<" "<<vertex2<<'\n';
  cout<<"Created"<<'\n';
}

void GraphEquation::CreateEdge(const string &s1, const string &s2, const string &mathOperator, const Bools &b1, const Bools &b2, const uint8_t id)
{
  cout<<" "<<'\n';
  if(b1.variable and b2.variable)
    {
      CreateVertex<VertexVariable, VertexVariable, EdgeVariable, EdgeVariable>(s1, s2, mathOperator, id);
    }
  else if(b1.variable and b2.constant)
    {
      CreateVertex<VertexVariable, VertexConstant, EdgeVariable, EdgeConstant>(s1, s2, mathOperator, id);
    }
  else if(b1.variable and b2.numeric)
    {
      CreateVertexNumeric<VertexVariable, VertexVerticesNumeric2>(s2, s1, mathOperator, id);
    }
  else if(b1.constant and b2.variable)
    {
      CreateVertex<VertexConstant, VertexVariable, EdgeConstant, EdgeVariable>(s1, s2, mathOperator, id);
    }
  else if(b1.constant and b2.constant)
    {
      CreateVertex<VertexConstant, VertexConstant, EdgeConstant, EdgeConstant>(s1, s2, mathOperator, id);
    }
  else if(b1.constant and b2.numeric)
    {
      CreateVertexNumeric<VertexConstant, VertexVerticesNumeric2>(s2, s1, mathOperator, id);
    }
  else if(b1.numeric and b2.variable)
    {
      cout<<"b1.numeric and b2.variable"<<'\n';
      CreateVertexNumeric<VertexVariable, VertexVerticesNumeric1>(s1, s2, mathOperator, id);
    }
  else if(b1.numeric and b2.constant)
    {
      CreateVertexNumeric<VertexConstant, VertexVerticesNumeric1>(s1, s2, mathOperator, id);
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
  else if(b1.math)
    {
      cout<<"b1.math"<<'\n';
      VertexVertices *v1=new VertexVertices(vmap[s1], vmap[s2], mathOperator);
      vmap["@"+std::to_string(id)]=v1;
    }
  else if(b1.numeric and b2.math and vmap[s2]->GetValue()!=NAN)
    {
      // Result can be calculated in advance, so the equation template can
      // be simplified and performance of the calculation increased.
      VertexMultiValue *v1=new VertexMultiValue(mathOperator);
      Vertex *v=new VertexNumeric(v1->GetOperator(std::stod(s1), vmap[s2]->GetValue()));
      cout<<"vmap[s1].GetValue()!=NAN "<<s1<<" "<<vmap[s2]->GetValue()<<" "<<v->GetValue()<<'\n';
      vmap["@"+std::to_string(id)]=v;
      delete v1;
    }
  else if(b2.math)
    {
      cout<<"b2.math"<<'\n';
      VertexVertices *v2=new VertexVertices(vmap[s2], vmap[s1], mathOperator);
      vmap["@"+std::to_string(id)]=v2;
    }
  else if(b2.numeric and b1.math and vmap[s1]->GetValue()!=NAN)
    {
      // Result can be calculated in advance, so the equation template can
      // be simplified and performance of the calculation increased.
      VertexMultiValue *v1=new VertexMultiValue(mathOperator);
      Vertex *v=new VertexNumeric(v1->GetOperator(vmap[s2]->GetValue(), std::stod(s1)));
      cout<<"vmap[s1].GetValue()!=NAN "<<s2<<" "<<vmap[s1]->GetValue()<<" "<<v->GetValue()<<'\n';
      vmap["@"+std::to_string(id)]=v;
      delete v1;
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
