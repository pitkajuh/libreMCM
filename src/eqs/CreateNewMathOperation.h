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

template<typename T, typename U, typename L>
MathOperation *CreateNewMathOperation(const string &s1, const string &s2, const string &o, const unsigned int &k)
{
  VaVaMathOperation *m=new L;
  m->SetV1(new T);
  m->SetV1Value(stod(s1));
  m->SetV2(new U);
  m->SetV2Name(s2);
  m->SetOperator(o);
  m->id=k;
  return m;
}

template<typename T, typename U, typename L>
MathOperation *CreateNewMathOperation2(const string &s1, const string &s2, const string &o, const unsigned int &k)
{
  VaVaMathOperation *m=new L;
  m->SetV1(new T);
  m->SetV1Name(s1);
  m->SetV2(new U);
  m->SetV2Name(s2);
  m->SetOperator(o);
  m->id=k;
  return m;
}

#endif
