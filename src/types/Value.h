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
  void SetName(const string &s){name=s;}
  void SetValue(const double &v)
  {
    // cout<<"SetValue"<<'\n';
    value=v;
  }
  string GetName(){return name;}
  double GetValue(){return value;}
  virtual Value *Clone()=0;
};

class Constant: public Value
{
 public:
  Constant(const string &s){SetName(s);}
};

class Variable: public Value
{
public:
  Variable(const string &s){SetName(s);}
};

class Numeric: public Value
{
public:
  Numeric(const double &v){SetValue(v);}
  Numeric *Clone()
  {
    // cout<<"Cloning Numeric"<<'\n';
    return new Numeric(*this);
  }
};

class InitialValue: public Value
{
public:
};

class MathOperationValue: public Value
{
public:
};

#endif
