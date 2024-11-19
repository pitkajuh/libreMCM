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
#include <math.h>
#include "../inc/namespace.h"

using namespace libremcm;

class Value
{
protected:
  string name;
  double value=NAN;
  bool isNegative=0;
public:
  void SetName(const string &s)
  {
    name=s;

    if(s[0]=='-')
      {
	isNegative=1;
	name=name.substr(1, name.size());
      }
  }
  void SetValue(const double v)
  {
    value=v;

    if(isNegative) value=-1*value;
  }
  const string GetName(){return name;}
  double GetValue(){return value;}
  Value(){};
  Value(const Value &v)
  {
    std::cout<<"Value copy"<<'\n';
    this->name=v.name;
    this->value=v.value;
    this->isNegative=v.isNegative;
  }
  virtual ~Value(){}
};

class Constant: public Value
{
 public:
  Constant(const string &s){SetName(s);}
  Constant(){}
};

class Variable: public Value
{
public:
  Variable(const string &s){SetName(s);}
  Variable(){}
};

class Numeric: public Value
{
public:
  Numeric(const string &s){SetValue(std::stod(s));}
  Numeric(const double s){SetValue(s);}
  Numeric(){}
};

#endif
