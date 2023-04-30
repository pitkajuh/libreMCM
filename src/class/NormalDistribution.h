/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef NORMALDISTRIBUTION_H
#define NORMALDISTRIBUTION_H

#include <string>
#include "ProbabilisticDistribution.h"
#include "../math/mcm_pdf_normal.h"

using std::string;

class NormalDistribution: public ProbabilisticDistribution
{
public:
  double pdf(const double value)
  {
    return mcm_pdf_normal(value);
  }
  double cdf(const double value)
  {
    return mcm_cdf_normal(value);
  }
};

#endif
