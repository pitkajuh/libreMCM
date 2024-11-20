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
  bool negative=0;
public:
  void SetName(const string &s)
  {
    name=s;

    if(s[0]=='-')
      {
	negative=1;
	name=name.substr(1, name.size());
      }
  }
  void SetValue(const double v)
  {
    value=v;

    if(negative) value=-1*value;
  }
  bool GetNegative(){return negative;}
  const string GetName(){return name;}
  double GetValue(){return value;}
  Value(){};
  Value(const Value &v)
  {
    std::cout<<"Value copy"<<'\n';
    this->name=v.name;
    this->value=v.value;
    this->negative=v.negative;
  }
  Value &operator=(Value &v)
  {
    std:: cout<<"Value ="<<'\n';
    if(this==&v) return *this;

    this->name=v.GetName();
    this->value=v.GetValue();
    this->negative=v.GetNegative();

    return *this;
  }
  virtual Value *clone() const {return new Value(*this);}
  virtual ~Value(){}
};

class Constant: public Value
{
 public:
  Constant(const string &s){SetName(s);}
  Constant(){}
  Constant(Value &v)
  {
    std::cout<<"Constant copy"<<'\n';
    this->name=v.GetName();
    this->value=v.GetValue();
    this->negative=v.GetNegative();
  }
  Constant &operator=(Value &v)
  {
    std:: cout<<"Value ="<<'\n';
    if(this==&v) return *this;

    this->name=v.GetName();
    this->value=v.GetValue();
    this->negative=v.GetNegative();

    return *this;
  }
  Constant *clone() const override {return new Constant(*this);}
};

class Variable: public Value
{
public:
  Variable(const string &s){SetName(s);}
  Variable(){}
  Variable(Value &v)
  {
    std::cout<<"Variable copy"<<'\n';
    this->name=v.GetName();
    this->value=v.GetValue();
    this->negative=v.GetNegative();
  }
  Variable &operator=(Value &v)
  {
    std:: cout<<"Value ="<<'\n';
    if(this==&v) return *this;

    this->name=v.GetName();
    this->value=v.GetValue();
    this->negative=v.GetNegative();

    return *this;
  }
  Variable *clone() const override {return new Variable(*this);}
};

class Numeric: public Value
{
public:
  Numeric(const string &s){SetValue(std::stod(s));}
  Numeric(const double s){SetValue(s);}
  Numeric(){}
  Numeric(Value &v)
  {
    std::cout<<"Numeric copy"<<'\n';
    this->value=v.GetValue();
    this->negative=v.GetNegative();
  }
  Numeric &operator=(Value &v)
  {
    std:: cout<<"Value ="<<'\n';
    if(this==&v) return *this;

    this->value=v.GetValue();
    this->negative=v.GetNegative();

    return *this;
  }
  Numeric *clone() const override {return new Numeric(*this);}
};

#endif
