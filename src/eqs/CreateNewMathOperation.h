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

void printeq(Equation *m)
{
  Equation *c=m;
  cout<<"PRINTING"<<'\n';

  while(c!=nullptr)
    {
      // cout<<"find "<<i<<" now "<<c->id<<" "<<c->next<<'\n';
      cout<<c->id<<" "<<c<<" "<<c->next<<'\n';

      // cout<<"Not found, next"<<'\n';
      c=c->next;
    }
  cout<<" "<<'\n';
}

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

Equation *FindPrevious(Equation *m, Equation *f)
{
  Equation *c=m;

  while(c!=nullptr)
    {
      if(c==f->next) return c;
      c=c->next;
    }

  return nullptr;
}

void Select(Equation *&e, Equation *&next, Equation *&m, const unsigned &k, const unsigned &s1, EquationMath *&mc)
{
  cout<<" "<<'\n';
  cout<<"Select "<<m->id<<'\n';
  // printeq(mc);
  // printeq(m);
  // printeq(e);

  // if(m->next!=nullptr)
  //   {
  //     cout<<"m->next!=nullptr "<<m->next<<'\n';
  //     cout<<"setting "<<m->next<<" to "<<FindPrevious(e, m)->next<<'\n';
  //     // mc->next=Search2(e, m)->next;

  //     // m->next=FindPrevious(e, m)->next;
  //     // mc->next=m->next;

  //   }
  // else
  //   {
  //     cout<<"m->next==nullptr "<<m->next<<" "<<Search2(e, m)<<'\n';
  //     // Search2(e, m)->next=nullptr;
  //     // mc->next=Search2(e, m);
  //   }

  if(s1>0)
    {
      cout<<"s1>0"<<'\n';

      if(k-s1==1)
	{
	  // Change next only from one direction.
	  cout<<"k-s1==1"<<'\n';

	  cout<<Search2(e, m)->next<<'\n';
	  mc->next=Search2(e, m)->next;
	}
      else
	{
	  cout<<"k-s1>1"<<'\n';

	  cout<<Search2(e, m)->id<<" "<<k<<'\n';

	  if(k-Search2(e, m)->id==1)
	    {
	      cout<<"k-Search2(e, m)->id==1"<<'\n';
	    }

	  // if(m->next==nullptr)
	  //   {
	      // Change next only from one direction.
	      cout<<"m->next==nullptr "<<k<<" "<<s1<<'\n';
	      cout<<Search2(e, m)<<" "<<Search2(e, m)->next<<" find prev node "<<FindPrevious(e, m)<<" "<<'\n';
	      // Search2(e, m)->next=nullptr;



	      Search2(e, m)->next=m->next;
	      // cout<<mc<<" "<<mc->next<<'\n';

	      // mc->next=Search2(e, m)->next;
	      // mc->next=m->next;

	      // mc->next=m->next;
	      // mc->next=nullptr;
	      // printeq(mc);
	  //   }
	  // else
	  //   {
	  //   // Change next from two directions.
	  //     cout<<"m->next==nullptr else"<<'\n';
	  // }
	  cout<<"s1 "<<s1<<" m "<<m<<" "<<m->next<<'\n';
	}
    }
  else
    {
      cout<<"s1>0 else Search2(e, m) "<<Search2(e, m)->id<<" "<<Search2(e, m)<<" "<<Search2(e, m)->next<<" m "<<m<<" "<<m->next<<'\n';
      // cout<<"s1>0 else FindPrevious(e, m) "<<FindPrevious(e, m)<<" "<<FindPrevious(e, m)->next<<" m "<<m<<" "<<m->next<<'\n';
      Search2(e, m)->next=nullptr;
      // Search2(e, m)->next=m->next;

      // mc->next=Search2(e, m)->next;
      // mc->next->next=nullptr;

    }

  printeq(mc);
  cout<<" "<<'\n';
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
  cout<<"r "<<r<<'\n';
  const double result=r->result;
  const double v_value=mc->v->GetValue();

  if(!isnan(result) and !isnan(v_value)) mc->CalculateResult(result);
  else  e->m1=r->m1;
  r->m1=nullptr;

  // Select<Equation>(e, next, r, k, stoi(s1.substr(1, s1.size())), e);
      // printeq(e);
  if(k-r->id==1)
    {
      cout<<"k-r->id==1 "<<k<<" "<<r->id<<'\n';
      cout<<e<<" Setting "<<e->next<<" to "<<r->next<<'\n';
      // printeq(e);
      e->next=r->next;
      // r->next=nullptr;
      // printeq(e);
    }
  else
    {
      Equation *prev=Search2(c, r);

      cout<<" "<<'\n';
      cout<<"id "<<prev->id<<" "<<prev<<" "<<prev->next<<'\n';

      if(r->id>0 and r->next!=nullptr)
	{
	  cout<<"r->id>0 and r->next!=nullptr"<<'\n';
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
  // printeq(e);
  // r=nullptr;
  delete r;
  // printeq(e);
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
