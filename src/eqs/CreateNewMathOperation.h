/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef CREATENEWMATHOPERATION_H
#define CREATENEWMATHOPERATION_H

#include "../types/MathOperation.h"

MathOperation *Search(MathOperation *m, const unsigned int i)
{
  MathOperation *c=m;

  while(c!=nullptr)
    {
      if(c->id==i) return c;
      c=c->next;
    }
  return nullptr;
}

template<typename T, typename U>
MathOperation *NewMathValue(const string &s1, const string &s2, const string &o, const unsigned int &k, MathOperation *&c)
{
  ValueMath *m=new T;
  m->SetV(new U(s2));
  m->id=k;
  MathOperation *r=Search(c, stoi(s1.substr(1, s1.size())));
  cout<<"v "<<r->id<<" "<<r->GetV1()<<'\n';
  const double result=r->result;
  cout<<"id "<<r->id<<'\n';
  if(!isnan(result))
    {
      // Only result will be taken into account, v1, v2 and math_operator can be omitted.
      m->SetV1(nullptr);
      m->SetV2(nullptr);
      m->SetOperator(nullptr);
      m->result_total=result;
    }
  else
    {
      cout<<"else NewMVMath"<<'\n';
      m->SetV1(r->GetV1()->New(r->GetV1()));
      m->SetV2(r->GetV2()->New(r->GetV2()));
      m->SetOp(r->GetOp()->New());
    }

  m->SetOperator1(o);
  r->next=nullptr;
  delete r;
  return m;
}

template<typename T, typename U, typename L>
MathOperation *CreateNewMathOperation(const string &s1, const string &s2, const string &o, const unsigned int &k)
{
  MathOperation *m=new L;
  m->SetV1(new T(s1));
  m->SetV2(new U(s2));
  m->SetOperator(o);
  m->id=k;
  return m;
}

#endif
