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

Equation *Search(Equation *&m, const unsigned &i)
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

Equation *Search2(Equation *&m, Equation *&f)
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

// Equation *FindPrevious(Equation *m, Equation *f)
// {
//   Equation *c=m;

//   while(c!=nullptr)
//     {
//       if(c==f->next) return c;
//       c=c->next;
//     }

//   return nullptr;
// }

void Select(Equation *&head, Equation *&node, EquationMath *&newnode)
{
  if(head==node) newnode->next=Search2(head, node)->next;
  else
    {
      newnode->next=head;
      Search2(head, node)->next=node->next;
    }
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
