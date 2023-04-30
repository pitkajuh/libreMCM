/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef CONSTANTPROBABILISTICDATA_H
#define CONSTANTPROBABILISTICDATA_H

#include <string>

using std::string;

class ConstantProbabilisticData
{
public:
  string pdf_type;
  string stdev;
  string lower_bound;
  string upper_bound;
};

#endif
