/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef DATA_H
#define DATA_H

#include <vector>
#include "Equation.h"
#include "../inc/namespace.h"

using std::vector;

using namespace libremcm;
using InitialValues=SMap;

struct Data
{
  vector<string> diagonal;
  SMap constants_map;

  Data(const vector<string> &d, const SMap &cm)
  {
    diagonal=d;
    constants_map=cm;
  }
};

#endif
