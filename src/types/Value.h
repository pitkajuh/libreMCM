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
#include <vector>
#include <math.h>
#include "MathOperation.h"

using std::string;

class Value
{
public:
  string name="";
  double value=0;

  void SetName(const string &s) {name=s;}
  void SetValue(const double &v) {value=v;}
  virtual void Link()=0;
};

class Constant: public Value
{
 public:
  void Link(){}
};

class Variable: public Value
{
public:
  void Link(){}
};

class Numeric: public Value
{
public:
  void Link(){}
};

class InitialValue: public Value
{
public:
  void Link(){}
};

class MathOperationValue: public Value
{
public:
  void Link(){}
};

class RadioNuclide: public InitialValue
{
public:
  double halflife;
  void Link(){}
  // double ExpDecay(const double &t)
  // {
  //   return value*exp(-log(2)*t/halflife);
  // }

};

#endif
