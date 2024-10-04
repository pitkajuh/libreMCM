/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef ISIN_H
#define ISIN_H

#include <vector>
#include "../inc/namespace.h"

using namespace libremcm;
using std::vector;

const bool IsNumerical(const string &s);
const bool IsIn(const string &s, const SMap &f);
const bool IsIn(const string &s, const vector<string> &f);

#endif
