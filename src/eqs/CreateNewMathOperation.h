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

Equation *Search(Equation *m, const unsigned &i)
{
  Equation *c=m;
  cout<<"find "<<i<<'\n';
  while(c!=nullptr)
    {
      // cout<<"find "<<i<<" now "<<c->id<<'\n';
      // cout<<"find "<<i<<"  "<<'\n';
      if(c->id==i)
	{
	  // cout<<"found"<<'\n';
	  return c;
	}
      c=c->next;
    }
  cout<<"Warning id "<<i<<" not found"<<'\n';
  return nullptr;
}

template<typename T, typename U>
EquationOperationValueBase *NewMathValue(const string &s1, const string &s2, const string &o, const unsigned &k, Equation *&c, Equation *&next)
{
  Equation *e=new Equation;
  EquationOperationValueBase *mc=new U;
  mc->v=new T(s2);
  mc->SetOperator(o);
  e->id=k;

  Equation *r=Search(c, stoi(s1.substr(1, s1.size())));
  const double result=r->result;
  const double v_value=mc->v->GetValue();

  // cout<<"mc->next "<<mc->next<<'\n';
  // cout<<"r->next "<<r->next<<'\n';

  if(!isnan(result) and !isnan(v_value)) mc->CalculateResult(result);
  else
    {
      e->m1=r->m1;
      // mc->m1=mc;
    }

  cout<<"delete "<<r<<'\n';
  if(r->next!=nullptr)
    {
      // mc->next=r->next;
      e->next=r->next;
    }
  else
    {
      // mc->next=next;
      e->next=next;
    }
  // cout<<"mc->next "<<mc->next<<'\n';

  // r->next->next=mc->next;
  // mc->next=r->next;
  // Search(c, stoi(s1.substr(1, s1.size()))-1)->next=nullptr;
  delete r;
  return mc;
}

template<typename T, typename U, typename L>
MathOperation *CreateNewMathOperation(const string &s1, const string &s2, const string &o)
{
  MathOperation *m=new L;
  m->SetV1(new T(s1));
  m->SetV2(new U(s2));
  m->SetOperator(o);
  return m;
}

#endif
