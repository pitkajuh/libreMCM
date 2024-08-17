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
#include "../types/Equation.h"

Equation *Search(Equation *m, const unsigned int i)
{
  Equation *c=m;

  while(c!=nullptr)
    {
      if(c->id==i) return c;
      c=c->next;
    }
  return nullptr;
}

// template<typename T, typename U>
template<typename T>
Equation *NewMathValue(const string &s1, const string &s2, const string &o, const unsigned int &k, Equation *&c, Equation *&next)
{
  EquationV *mc=new EquationV;
  mc->v=new T(s2);
  mc->SetOperator(o);
  mc->id=k;
  // ValueMath *m=new T;
  // m->SetV(new U(s2));
  // m->id=k;
  // mc->m2=m;

  Equation *r=Search(c, stoi(s1.substr(1, s1.size())));
  // r->next=nullptr;
  // c->next=nullptr;
  const double result=r->result;

  r->Type();
  if(!isnan(result))
    {
      cout<<"!isnan(result)"<<'\n';
      // Only result will be taken into account.
      mc->m1->result=result;
      // m->SetV1(nullptr);
      // m->SetV2(nullptr);
      // m->SetOperator(nullptr);
      // m->result_total=result;
    }
  else
    {
      cout<<"else"<<'\n';
      mc->m1=r->m1;

      r->m1=nullptr;
      delete r;
      next=nullptr;

      // r->next=nullptr;
      // m->SetV1(r->GetV1()->New(r->GetV1()));
      // m->SetV2(r->GetV2()->New(r->GetV2()));
      // m->SetOp(r->GetOp()->New());
    }
  cout<<"ao"<<'\n';
  // mc->next=nullptr;
  // r->next=nullptr;
  // c->next=nullptr;

  // m->SetOperator1(o);
  // // r->next=nullptr;

  // // next=nullptr;
  // // delete r;
  // delete next;
  // next=nullptr;
  // cout<<"mopertor "<<m<<" "<<m->GetV1()<<" "<<m->GetOp()<<" "<<m->GetV2()<<" "<<m->GetV()<<" "<<m->GetOp1()<<'\n';

  // delete mc;
  // return r;
  cout<<"mopertor "<<mc<<" "<<mc->m1<<" "<<mc->m1<<" "<<mc->m1->GetV1()<<" "<<mc->m1->GetOp()<<" "<<mc->m1->GetV2()<<'\n';
  return mc;
}

template<typename T, typename U, typename L>
MathOperation *CreateNewMathOperation(const string &s1, const string &s2, const string &o, const unsigned int &k)
{
  MathOperation *m=new L;
  m->SetV1(new T(s1));
  m->SetV2(new U(s2));
  m->SetOperator(o);
  m->id=k;
  cout<<"mopertor "<<m<<" "<<m->GetV1()<<" "<<m->GetOp()<<" "<<m->GetV2()<<'\n';
  return m;
}

#endif
