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
  // int ii=c->id;
  // cout<<"find "<<i<<'\n';
  while(c!=nullptr)
    {
      // cout<<"find "<<i<<" now "<<c->id<<" "<<c->next<<'\n';
      // cout<<"searching "<<i<<" now "<<c<<'\n';
      if(c->id==i)
	{
	  // cout<<"found "<<i<<'\n';
	  return c;
	}
      // cout<<"Not found, next"<<'\n';
      c=c->next;
    }
  cout<<"Warning id "<<i<<" not found"<<'\n';
  return nullptr;
}

Equation *Search2(Equation *m, Equation *f)
{
  Equation *c=m;
  // cout<<"find "<<f<<'\n';

  if(f==c)
    {
      // cout<<"return c;"<<'\n';
      return c;
    }

  while(c!=nullptr)
  // while(c!=f)
    {
      if(c->next==f)
	{
	  // cout<<"found "<<f<<" -> "<<c<<" "<<c->next<<'\n';
	  return c;
	}
      c=c->next;
    }
  cout<<"Warning id "<<f<<" not found"<<'\n';
  return nullptr;
}

template<typename T, typename U>
Equation *NewMathValue(const string &s1, const string &s2, const string &o, const unsigned &k, Equation *&c, Equation *&next, const unsigned &size)
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

  if(!isnan(result) and !isnan(v_value)) mc->CalculateResult(result);
  else  e->m1=r->m1;
  r->m1=nullptr;

  // cout<<"IDS "<<k<<" "<<r->id<<" size "<<size<<" r->next "<<r->next<<'\n';

  // if(k>r->id)
  //   {
  //     cout<<"k>r->id "<<"e->next "<<e->next<<" next "<<next<<" next->next "<<next->next<<'\n';
  //   }

  if(k-r->id==1)
    {
      cout<<"k-r->id==1 "<<k<<" "<<r->id<<'\n';
      e->next=r->next;
    }
  else
    {
      // cout<<"else k-r->id>1"<<'\n';
      Equation *prev=Search(c, stoi(s1.substr(1, s1.size()))+1);

      cout<<" "<<'\n';
      cout<<"id "<<prev->id<<" "<<prev<<" "<<prev->next<<'\n';

      if(r->id>0 and r->next!=nullptr)
      // if(r->id>0)
	{
	  cout<<"id "<<r->id<<" "<<r<<" "<<r->next<<'\n';
	  cout<<"id "<<r->next->id<<" "<<r->next<<" "<<r->next->next<<" "<<'\n';
	  prev->next=r->next->next;
	  cout<<""<<'\n';
	}
      else
	{
	  cout<<"id "<<r->id<<" "<<r<<" "<<r->next<<'\n';
	  prev->next=r->next;
	}
      cout<<" "<<'\n';
      e->next=next;
    }

  cout<<"Delete "<<r->id<<" r "<<r<<" r->next "<<r->next<<" "<<k<<'\n';
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
