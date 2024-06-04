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

// template<typename T>
class Value
{
public:
  string name;
  double value;



  // Value(string s, double v)
  // {
  //   name=s;
  //   value=v;
  // }
  void SetName(string s) name=s;
  void SetValue(double v value=v;
  /* ~Value(){} */
};

// template<typename T>
class Constant: public Value
{
public:

  Constant(string s, double v=0)
  {
    name=s;
    value=v;
  }

};

// template<typename T>
class Variable: public Value
{
public:


};

class InitialValue: public Value
{
public:

  // InitialValue(string s, double v=0)
  // {
  //   name=s;
  //   value=v;
  // }

};

class RadioNuclide: public InitialValue
{
private:
  double halflife;

};

#endif
