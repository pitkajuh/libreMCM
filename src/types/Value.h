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

    if(isNegative)
      {
	isNegative=0;
	value=-1*value;
      }
  }
  const string GetName(){return name;}
  double GetValue(){return value;}
  virtual ~Value(){}
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
  Numeric(const string &s){SetValue(std::stod(s));}
  Numeric(const double s){SetValue(s);}
};

#endif
