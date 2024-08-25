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
      // cout<<"find "<<i<<" now "<<c->id<<'\n';
      cout<<"find "<<i<<" now "<<'\n';
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
Equation *NewMathValue(const string &s1, const string &s2, const string &o, const unsigned int &k, Equation *&c, Equation *&next)
{
  // EquationV *mc=new U;
  EquationValueBase *mc=new U;
  mc->v=new T(s2);
  mc->SetOperator(o);
  mc->id=k;
  cout<<"s1 "<<s1<<'\n';
  Equation *r=Search(c, stoi(s1.substr(1, s1.size())));
  r->Type();
  const double result=r->result;
  const double v_value=mc->v->GetValue();
  cout<<"result "<<result<<'\n';

  if(!isnan(result) and !isnan(v_value))
    {
      cout<<"!isnan(result) "<<next<<'\n';
      // Only result will be taken into account.
      mc->m1=nullptr;
      mc->CalculateResult(result);
      cout<<"result is "<<mc->result<<'\n';
    }
  else
    {
      cout<<"else"<<'\n';
      mc->m1=r->m1;
      r->m1=nullptr;
      // cout<<"mopertor "<<mc<<" "<<mc->m1<<" "<<mc->m1<<" "<<mc->m1->GetV1()<<" "<<mc->m1->GetOp()<<" "<<mc->m1->GetV2()<<'\n';
    }

  delete r;
  next=nullptr;
  return mc;
}

template<typename T, typename U, typename L>
MathOperation *CreateNewMathOperation(const string &s1, const string &s2, const string &o, const unsigned int &k)
{
  MathOperation *m=new L;
  m->SetV1(new T(s1));
  m->SetV2(new U(s2));
  m->SetOperator(o);
  // cout<<"mopertor "<<m<<" "<<m->GetV1()<<" "<<m->GetOp()<<" "<<m->GetV2()<<'\n';
  return m;
}

#endif
