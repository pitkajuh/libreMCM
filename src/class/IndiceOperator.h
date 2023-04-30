/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef INDICEOPERATOR_H
#define INDICEOPERATOR_H

#include "../global/global_constants.h"
#include "../math/mcm_power.h"
#include "../math/mcm_sin.h"
#include "../math/mcm_cos.h"
#include "../math/mcm_sqrt.h"
#include "../math/mcm_log.h"
#include "../math/mcm_exp.h"
#include "../math/calculate_order_of_operations.h"

#include <iostream>
using std::cout;

class IndiceOperator
{
public:
  vector<string> exponent_vec;
  string exponent;
  virtual string get_result(const string value)=0;

  void set_expvec(const vector<string> exp)
  {
    exponent_vec=exp;
  }
};

class IndiceOperatorPower: public IndiceOperator
{
public:
  string get_result(const string value)
  {
    exponent_vec=calculate_order_of_operations(exponent_vec);
    exponent=exponent_vec.back();
    return mcm_power(value, exponent);
  }
};

class IndiceOperatorSin: public IndiceOperator
{
public:
  string get_result(const string value)
  {
    return mcm_sin(value);
  }
};

class IndiceOperatorCos: public IndiceOperator
{
public:
  string get_result(const string value)
  {
    return mcm_cos(value);
  }
};

class IndiceOperatorSqrt: public IndiceOperator
{
public:
  string get_result(const string value)
  {
    return mcm_sqrt(value);
  }
};

class IndiceOperatorLog: public IndiceOperator
{
public:
  string get_result(const string value)
  {
    return mcm_log(value);
  }
};

class IndiceOperatorExp: public IndiceOperator
{
public:
  string get_result(const string value)
  {
    return mcm_exp(value);
  }
};

#endif
