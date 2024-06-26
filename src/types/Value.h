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

  void SetName(const string &s) {name=s;}
  void SetValue(const double &v) {value=v;}
};

class Constant: public Value
{
 public:
};

class Variable: public Value
{
public:

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
