#include "Vertex.h"

void VertexValue::SetName(const string &s)
{
  name=s;

  if(s[0]=='-')
    {
      negative=1;
      name=name.substr(1, name.size());
    }
}

void VertexValue::SetValue(const double v)
{
  value=v;

  if(negative) value=-1*value;
}

const bool VertexValue::GetNegative(){return negative;}
const string VertexValue::GetName(){return name;}
void VertexValue::Calculate(){cout<<"VertexValue Calculate"<<'\n';}

double VertexConstant::GetValue(){return value;}
VertexConstant::VertexConstant(const string &s){SetName(s);}

double VertexNumeric::GetValue(){return value;}
VertexNumeric::VertexNumeric(const string &s){SetValue(stod(s));}
VertexNumeric::VertexNumeric(const double s){SetValue(s);}

double VertexVariable::GetValue(){return value;}
VertexVariable::VertexVariable(const string &s){SetName(s);}

void VertexMultiValue::SetOperator(const string &s)
{
  if(s=="+") mathOperator=new Add;
  else if(s=="-") mathOperator=new Sub;
  else if(s=="*") mathOperator=new Mul;
  else if(s=="/") mathOperator=new Div;
  else if(s=="^") mathOperator=new Exp;
}

double VertexMultiValue::GetOperator(const double d1, const double d2){return mathOperator->Calculate(d1, d2);}
double VertexMultiValue::GetValue(){return result;}
void VertexMultiValue::Calculate(){cout<<"VertexMultiValue Calculate"<<'\n';}
VertexMultiValue::VertexMultiValue(const string &s){this->SetOperator(s);}
VertexMultiValue::~VertexMultiValue(){delete mathOperator;}

void VertexVertices::Calculate()
{
  cout<<"VertexVertices Calculate"<<'\n';
  cout<<vertex1->GetValue()<<" "<<vertex2->GetValue()<<'\n';
  result=mathOperator->Calculate(vertex1->GetValue(), vertex2->GetValue());
  cout<<result<<'\n';
}
VertexVertices::VertexVertices(Vertex *vertex1, Vertex *vertex2, const string &s)
{
  this->vertex1=vertex1;
  this->vertex2=vertex2;
  this->SetOperator(s);
}

VertexVerticesNumeric1::VertexVerticesNumeric1(Vertex *vertex1, Vertex *vertex2, const string &s)
{
  cout<<"VertexVerticesNumeric1"<<'\n';
  this->vertex1=vertex1;
  this->vertex2=vertex2;
  this->SetOperator(s);
}

VertexVerticesNumeric1::~VertexVerticesNumeric1(){delete vertex1;}

VertexVerticesNumeric2::VertexVerticesNumeric2(Vertex *vertex1, Vertex *vertex2, const string &s)
{
  cout<<"VertexVerticesNumeric2"<<'\n';
  this->vertex1=vertex2;
  this->vertex2=vertex1;
  this->SetOperator(s);
}

VertexVerticesNumeric2::~VertexVerticesNumeric2(){delete vertex2;}
