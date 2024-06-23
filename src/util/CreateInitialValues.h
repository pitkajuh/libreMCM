/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef CREATEINITIALVALUES_H
#define CREATEINITIALVALUES_H

#include <string>
#include <unordered_map>
#include <vector>
using std::unordered_map;
using std::vector;
using std::string;

vector<string> CreateAllInitialValues(const unordered_map<string, InitialValues> &iv);

#endif
