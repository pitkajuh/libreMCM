/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef MCMPDFNORMAL_H
#define MCMPDFNORMAL_H

const double mcm_z_normal(const double value, const double mean, const double stdev);
const double mcm_cdf_normal(const double value, const double mean, const double stdev);
const double mcm_pdf_normal(const double value, const double mean, const double stdev, const double trmax, const double trmin);
const double mcm_pdf_value_normal(const double value, const double mean, const double stdev);

#endif
