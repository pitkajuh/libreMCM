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

using std::string;

class Value
{
public:
  string name;
  double value;

  void SetName(string s) name=s;
  void SetValue(double v value=v;
};

class Constant: public Value
{
 public:

  Constant(string s, double v=0)
    {
      name=s;
      value=v;
    }
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
private:
  double halflife;

};

#endif