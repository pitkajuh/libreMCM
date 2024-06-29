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

using std::string;

class Value
{
public:
  string name="";
  double value=0;

  Value(){};

  Value(const string &n, const double &v)
  {
    name=n;
    value=v;
  }

  // void Init(const string &name, const double &value)
  // {

  // }

  // void SetName(const string &s) {name=s;}
  // void SetValue(const double &v) {value=v;}
};

class Constant: public Value
{
 public:

  Constant(const string &n, const double &v)
    {
      name=n;
      value=v;
    }
};

class Variable: public Value
{
public:

  Variable(const string &n)
    {
      name=n;
    }

};

class InitialValue: public Value
{
public:

};

class RadioNuclide: public InitialValue
{
public:
  double halflife;

  // double ExpDecay(const double &t)
  // {
  //   return value*exp(-log(2)*t/halflife);
  // }

};

#endif
