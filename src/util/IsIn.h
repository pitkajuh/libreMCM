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
#include "../types/MathOperation.h"
#include "../inc/namespace.h"

using namespace libremcm;
using std::vector;
using MathOperations=Map<string, OpTmp>;

bool IsNumerical(const string &s);
bool IsIn(const string &s, const SMap &f);
bool IsIn(const string &s, const MathOperations &f);
bool IsIn(const string &s, const vector<string> &f);

#endif
