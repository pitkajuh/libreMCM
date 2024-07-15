/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef VALUE_H
#define VALUE_H

#include <iostream>
#include <string>

using std::string;
using std::cout;

class Value
{
private:
  string name;
  double value;
public:
  void SetName(const string &s) {name=s;}
  void SetValue(const double &v) {value=v;}
  string GetName() {return name;}
  double GetValue() {return value;}
};

class Constant: public Value
{
 public:
  Constant(const string &s)
  {
    SetName(s);
  }
};

class Variable: public Value
{
public:
  Variable(const string &s)
  {
    SetName(s);
  }
};

class Numeric: public Value
{
public:
  Numeric(const double &v)
  {
    SetValue(v);
  }
};

class InitialValue: public Value
{
public:
};

class MathOperationValue: public Value
{
public:
  // MathOperation *m;
  // MathOperationValue()
  // {
  //   cout<<"size "<<i<<"/"<<op.size()<<'\n';
  //   MathOperation *m=op[i];
  //   // Value *v1=m->GetV1();
  //   // Value *v2=m->GetV2();
  //    // const double s1=v1->GetValue();
  //    // const double s2=v2->GetValue();

  //    cout<<"Value "<<m->GetV1()->GetValue()<<" "<<m->GetV2()->GetValue()<<'\n';
  //   // const double s=m->Calculate();
  //    m->Calculate();
  //    // cout<<m->Calculate()<<'\n';
  //    delete m;
  // }
};

#endif
