/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef PROBABILISTICDISTRIBUTION_H
#define PROBABILISTICDISTRIBUTION_H

#include "../global/global_constants.h"

class ProbabilisticDistribution
{
public:
  double mean;
  double stdev;
  double trmax=INF;
  double trmin=NEG_INF;

  virtual double pdf(const double value, const double mean, const double stdev, const double trmax, const double trmin)=0;
  virtual double cdf(const double value)=0;
};

#endif
