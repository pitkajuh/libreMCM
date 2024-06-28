/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef PARSEINITIALVALUES_H
#define PARSEINITIALVALUES_H

#include <string>
#include <unordered_map>
#include <vector>
using std::unordered_map;
using std::vector;
using std::string;
using InitialValues=unordered_map<string, string>;
using DInitialValues=unordered_map<string, double>;

unordered_map<string, DInitialValues> ParseInitialValues(unordered_map<string, InitialValues> &ivs, const vector<string> &iv_names);

#endif
