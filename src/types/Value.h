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
#include <math.h>

using std::string;
using std::cout;

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

// class Constant: public Value
// {
//  public:
//   Constant(const string &s){SetName(s);}
// };

// class Variable: public Value
// {
// public:
//   Variable(const string &s){SetName(s);}
// };

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

// class InitialValue: public Value
// {
// public:
// };

// class MathOperationValue: public Value
// {
// public:
// };

#endif
