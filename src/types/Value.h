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
protected:
  string name;
private:
  double value=NAN;
public:
  void SetName(const string &s){name=s;}
  void SetValue(const double &v){value=v;}
  string GetName(){return name;}
  double GetValue(){return value;}
  virtual Value *New(Value *v)=0;
  virtual ~Value(){}
};

class Constant: public Value
{
 public:
  Constant(const string &s){SetName(s);}
  Value *New(Value *v)
  {
    Value *n=new Constant(v->GetName());
    n->SetValue(v->GetValue());
    return n;
  }
};

class Variable: public Value
{
public:
  Variable(const string &s){SetName(s);}
  Value *New(Value *v)
  {
    Value *n=new Variable(v->GetName());
    n->SetValue(v->GetValue());
    return n;
  }
};

class Numeric: public Value
{
public:
  Numeric(const string &s){SetValue(std::stod(s));}
  Numeric(const double &s){SetValue(s);}
  Value *New(Value *v)
  {
    Value *n=new Numeric(v->GetName());
    n->SetValue(v->GetValue());
    return n;
  }
};

#endif
