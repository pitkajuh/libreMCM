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
#include "../inc/namespace.h"

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
