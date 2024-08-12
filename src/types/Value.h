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

#include <string>
#include <math.h>

using std::string;

class Value
{
private:
  string name;
  double value=NAN;
public:
  void SetName(const string &s){name=s;}
  void SetValue(const double &v){value=v;}
  string GetName(){return name;}
  double GetValue(){return value;}
  Value()=default;
  virtual Value *New()=0;
};

class Constant: public Value
{
 public:
  Constant()=default;
  Value *New()
  {
    Value *n=new Constant;
    // n->SetName(v->GetName());
    // n->SetValue(v->GetValue());
    return n;
  }
};

class Variable: public Value
{
public:
  Variable()=default;
  Value *New()
  {
    Value *n=new Variable;
    // n->SetName(v->GetName());
    // n->SetValue(v->GetValue());
    return n;
  }
};

class Numeric: public Value
{
public:
  Numeric()=default;
  Value *New()
  {
    Value *n=new Numeric;
    // n->SetValue(v->GetValue());
    return n;
  }
};

#endif
