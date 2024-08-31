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
      cout<<"find "<<i<<" now "<<c->id<<" "<<c->next<<'\n';
      // cout<<"find "<<i<<"  "<<'\n';
      if(c->id==i)
	{
	  cout<<"found"<<'\n';
	  return c;
	}
      c=c->next;
    }
  cout<<"Warning id "<<i<<" not found"<<'\n';
  return nullptr;
}

template<typename T, typename U>
Equation *NewMathValue(const string &s1, const string &s2, const string &o, const unsigned &k, Equation *&c, Equation *&next)
{
  cout<<"NewMathValue"<<'\n';
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
  else  e->m1=r->m1;
  r->m1=nullptr;
  cout<<"delete "<<r<<'\n';

  // if(r->next!=nullptr)
  //   {
  //     cout<<"r->next!=nullptr"<<'\n';
  //     // mc->next=r->next;
  //     e->next=r->next;
  //   }
  // else
  //   {
  //     cout<<"else"<<'\n';
  //     // mc->next=next;
      e->next=next;
    // }


  // cout<<"mc->next "<<mc->next<<'\n';

  // r->next->next=mc->next;
  // mc->next=r->next;
  // Search(c, stoi(s1.substr(1, s1.size()))-1)->next=nullptr;
  // mc=nullptr;

      cout<<"IDS "<<k<<" "<<r->id<<'\n';
      // if(k-r->id>1 and r->next!=nullptr)
      if(k-r->id==1 and r->next==nullptr)
	{
	  cout<<"k-r->id==1 and r->next==nullptr"<<'\n';
	  // r->next=next;
	  // e->next=r->next;
	}
      if(k-r->id==1 and r->next!=nullptr)
	{
	  cout<<"k-r->id==1 and r->next!=nullptr"<<'\n';
	  // r->next=next; // NONONONO
	  e->next=r->next;
	}

      if(k-r->id>1 and r->next==nullptr)
	{
	  cout<<"k-r->id>1 and r->next==nullptr"<<'\n';
	  // r->next=next; // NO
	  // e->next=r->next; // NO
	}
      if(k-r->id>1 and r->next!=nullptr)
	{
	  cout<<"k-r->id>1 and r->next!=nullptr"<<'\n';
	  // r->next=next;
	  // e->next=r->next;
	}
  delete mc;
  delete r;
  return e;
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
