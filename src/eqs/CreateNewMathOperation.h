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
#include <iostream>
using std::cout;

void printeq(Equation *m)
{
  Equation *c=m;
  cout<<"PRINTING"<<'\n';

  while(c!=nullptr)
    {
      cout<<std::to_string(c->GetId())<<" "<<c<<" "<<c->next<<'\n';
      c=c->next;
    }
  cout<<" "<<'\n';
}

Equation *Search(Equation *&m, const uint8_t i)
{
  // Find node from linked list m by number.
  Equation *c=m;

  while(c!=nullptr)
    {
      if(c->GetId()==i) return c;
      c=c->next;
    }
  return nullptr;
}

Equation *Search2(Equation *&m, Equation *&f)
{
    // Find node from linked list m by memory address of f.
  if(f==m) return m;

  Equation *c=m;

  while(c!=nullptr)
    {
      if(c->next==f) return c;
      c=c->next;
    }
  return nullptr;
}

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
Equation *NewMathValue(const string &s1, const string &s2, const string &o, const uint8_t id, Equation *&head, Equation *&next)
{
  EquationValue *newhead=new U;
  newhead->SetId(id);
  newhead->v=new T(s2);
  newhead->SetOperator(o);
  Equation *r=Search(head, stoi(s1.substr(1, s1.size())));
  const double result=r->result;
  printf("NewMathValue\n");
  r->GetType();
  if(!isnan(result) and !isnan(newhead->v->GetValue())) newhead->CalculateResult(result);
  else newhead->m1=r->m1;
  r->m1=nullptr;

  if(id-r->GetId()==1) newhead->next=r->next;
  else
    {
      Equation *prev=Search2(head, r);
      prev->GetType();
      if(r->next!=nullptr) prev->next=r->next->next;
      else prev->next=r->next;
      newhead->next=next;
    }

  cout<<"Delete "<<std::to_string(r->GetId())<<" r "<<r<<" r->next "<<r->next<<" "<<std::to_string(id)<<'\n';
  delete r;
  return newhead;
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
