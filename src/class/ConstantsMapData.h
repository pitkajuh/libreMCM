/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef CONSTANTSMAPDATA_H
#define CONSTANTSMAPDATA_H

#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;

class ConstantsMapData
{
 public:
  // A default value. Used if initial value does not require specific value.
  string default_value;
  // A specific value. Used if initial value requires specific value, i.e. constant value (e.g. radionuclide).
  unordered_map<string, string> specific_value;
  string pdf;
  double stdev;
  double trmax;
  double trmin;
  vector<string> default_rnd_values;
  unordered_map<string, vector<string>> specific_rnd_values;
};

#endif
