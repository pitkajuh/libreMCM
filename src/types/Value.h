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
#include <string>
#include <math.h>

using std::string;
using std::cout;

class Value
{
private:
  // string name;
  // double value;
public:
  string name;
  double value;
  void SetName(const string &s){name=s;}
  void SetValue(const double &v)
  {
    // cout<<"SetValue"<<'\n';
    value=v;
  }
  string GetName(){return name;}
  double GetValue(){return value;}
  Value()=default;
  virtual Value *Clone()=0;
  virtual void Type()=0;
  Value(const Value &v)
  {
    cout<<"Value copy cost"<<'\n';
    name=v.name;
    value=v.value;
  }
  // Value(Value &&v)
  // {
  //   name=v.name;
  //   value=v.value;
  // }
  // ~Value()
  // {
  //   cout<<"~Value()"<<'\n';
  //   // free(name);
  //   // free(value);
  //   // name="";
  //   // value=NAN;
  // }
};

// class Constant: public Value
// {
//  public:
//   Constant(const string &s){SetName(s);}
// };

// class Variable: public Value
// {
// public:
//   Variable(const string &s){SetName(s);}
// };

class Numeric: public Value
{
public:
  Numeric(const double &v){SetValue(v);}
  Numeric *Clone()
  {
    // cout<<"Cloning Numeric"<<'\n';
    return new Numeric(*this);
  }
  void Type(){cout<<"Numeric"<<'\n';}
  Numeric(const Numeric &v)
  {
    cout<<"Value Numeric copy cost"<<'\n';
    value=v.value;
  }
  // Value(const Value &&v){value=v.value;}
};

// class InitialValue: public Value
// {
// public:
// };

// class MathOperationValue: public Value
// {
// public:
// };

#endif
