/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <cmath>
#include "../class/ProbabilisticDistribution.h"
#include "../global/pi.h"
#include "../util/d2str.h"
#include "../util/s2d.h"

const double mcm_z_normal(const double value, const double mean, const double stdev)
{
  const double z=(value-mean)/stdev;
  return z;
}

const double mcm_cdf_normal(const double value, const double mean, const double stdev)
{
  double z=mcm_z_normal(value, mean, stdev);
  const double cdf=0.5*(1-erf(z/sqrt(2)));
  return cdf;
}

const double pdf_value_update(const double pdf_value, const double trmax_value, const double trmin_value)
{
  const double result=pdf_value/(trmax_value-trmin_value);
  return result;
}

const double mcm_pdf_value_normal(const double value, const double mean, const double stdev)
{
  const double value_z=mcm_z_normal(value, mean, stdev);
  const double pdf=(1/(stdev*sqrt(2*PI_VAL)))*exp(-0.5*pow(value_z, 2));
  return pdf;
}

const double mcm_pdf_normal(const double value, const double mean, const double stdev, const double trmax, const double trmin)
{
  // Calculates value from normal distribution. The normal distribution can be truncated by setting inputs trmax and trmin to something else than inf and -inf.
  const double value_z=mcm_z_normal(value, mean, stdev);
  double pdf=(1/(stdev*sqrt(2*PI_VAL)))*exp(-0.5*pow(value_z, 2));
  double cdf_max;
  double cdf_min;

  if(trmax==INF and trmin==NEG_INF)
    {
      cdf_max=1;
      cdf_min=0;
    }
  else if(trmax==INF and trmin!=NEG_INF)
    {
      cdf_max=1;
      cdf_min=mcm_cdf_normal(trmin, mean, stdev);
    }
  else if(trmax!=INF and trmin==NEG_INF)
    {
      cdf_min=0;
      cdf_max=mcm_cdf_normal(trmax, mean, stdev);
    }
  else
    {
      cdf_max=mcm_cdf_normal(trmax, mean, stdev);
      cdf_min=mcm_cdf_normal(trmin, mean, stdev);
    }

  pdf=pdf_value_update(pdf, cdf_max, cdf_min);
  return pdf;
}
