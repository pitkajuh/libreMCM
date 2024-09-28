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
  // Find node from linked list m by id.
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

template<typename T>
void SetNext(T *&newhead, Equation *head, Equation *next, Equation *found, const uint8_t id)
{
  if(id-found->GetId()==1) newhead->next=found->next;
  else
    {
      Equation *prev=Search2(head, found);
      prev->GetType();
      if(found->next!=nullptr) prev->next=found->next->next;
      else prev->next=found->next;
      newhead->next=next;
    }
}

template<typename T, typename U>
Equation *NewMathValue(const string &s1, const string &s2, const string &o, const uint8_t id, Equation *&head, Equation *&next)
{
  EquationValue *newhead=new U;
  newhead->SetId(id);
  newhead->SetValue(new T(s2));
  newhead->SetOperator(o);
  Equation *found=Search(head, stoi(s1.substr(1, s1.size())));
  newhead->Set(found);
  newhead->Get()->GetType();
  cout<<"result "<<newhead->GetValue()->GetValue()<<" "<<found->result<<'\n';

  if(!isnan(found->result) and !isnan(newhead->GetValue()->GetValue()))
    {
      // The calculation can already be done here, thus the return type can
      // be reduced to Equation. All member values of newhead can be deleted
      // with the exception of result and id, which are transfered to new Equation.
      newhead->Calculate();
      Equation *newhead1=new Equation;
      newhead1->SetId(newhead->GetId());
      newhead1->result=newhead->result;
      newhead1->next=newhead->next;

      SetNext<Equation>(newhead1, head, next, found, id);
      printeq(newhead1);
      delete newhead;
      return newhead1;
      cout<<"newhead->Calculate(result) "<<newhead->result<<'\n';
    }
  else
    {
      newhead->m1=found->m1;
      found->m1=nullptr;
    }

  SetNext<EquationValue>(newhead, head, next, found, id);
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
