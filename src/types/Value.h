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

using std::string;

class Value
{
private:
  string name;
  double value;
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
    return n;
  }
};

#endif
