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
  Value *v1=new T;
  v1->SetValue((stod(s1)));
  Value *v2=new U;
  v2->SetName(s2);
  MathOperation *m=new L;
  m->id=k;
  m->Set(v1, o, v2);
  return m;
}

template<typename T, typename U, typename L>
MathOperation *CreateNewMathOperation2(const string &s1, const string &s2, const string &o, const unsigned int &k)
{
  Value *v1=new T;
  v1->SetName(s1);
  Value *v2=new U;
  v2->SetName(s2);
  MathOperation *m=new L;
  m->id=k;
  m->Set(v1, o, v2);
  return m;
}

#endif
