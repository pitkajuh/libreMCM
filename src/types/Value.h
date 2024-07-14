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
#include "MathOperation.h"
// using MathOperations=std::vector<MathOperation*>;
// typedef MathOperations std::vector<MathOperation*>;
using std::string;

class Value
{
private:
  string name;
  double value;
public:
  void SetName(const string &s) {name=s;}
  void SetValue(const double &v) {value=v;}
  string GetName() {return name;}
  double GetValue() {return value;}
};

class Constant: public Value
{
 public:
  Constant(const string &s)
  {
    SetName(s);
  }
};

class Variable: public Value
{
public:
  Variable(const string &s)
  {
    SetName(s);
  }
};

class Numeric: public Value
{
public:
  Numeric(const double &v)
  {
    SetValue(v);
  }
};

class InitialValue: public Value
{
public:
};

class MathOperationValue: public Value
{
public:
  // void Test(MathOperations &op, const unsigned int i)
  // {
  //   // MathOperation *m=op[i];
  // }
};

class RadioNuclide: public InitialValue
{
private:
  double halflife;
public:
};

#endif
