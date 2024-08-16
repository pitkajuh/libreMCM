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

// Equation *Search(Equation *m, const unsigned int i)
// {
//   Equation *c=m;

//   while(c!=nullptr)
//     {
//       if(c->id==i){return c;}
//       c=c->next;
//     }
//   return nullptr;
// }

// template<typename T, typename U>
// Equation *NewMathValue(const string &s1, const string &s2, const string &o, const unsigned int &k, Equation *&c, Equation *&next)
// {
//   // ValueMath *m=new T;
//   // m->SetV(new U(s2));
//   // m->id=k;
//   Equation *r=Search(c, stoi(s1.substr(1, s1.size())));
//   // const double result=r->result;

//   // if(!isnan(result))
//   //   {
//   //     // Only result will be taken into account, v1, v2 and math_operator can be omitted.
//   //     m->SetV1(nullptr);
//   //     m->SetV2(nullptr);
//   //     m->SetOperator(nullptr);
//   //     m->result_total=result;
//   //   }
//   // else
//   //   {
//   //     m->SetV1(r->GetV1()->New(r->GetV1()));
//   //     m->SetV2(r->GetV2()->New(r->GetV2()));
//   //     m->SetOp(r->GetOp()->New());
//   //   }

//   // m->SetOperator1(o);
//   // // r->next=nullptr;

//   // // next=nullptr;
//   // // delete r;
//   // delete next;
//   // next=nullptr;
//   // cout<<"mopertor "<<m<<" "<<m->GetV1()<<" "<<m->GetOp()<<" "<<m->GetV2()<<" "<<m->GetV()<<" "<<m->GetOp1()<<'\n';
//   return m;
// }

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
