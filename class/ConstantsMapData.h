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
#include <map>

using std::string;
using std::map;

class ConstantsMapData
{
 public:
  // An unspecified value. Used if initial value does not require specified value.
  string unspecific_value;
  // A specified value. Used if initial value requires specified value, i.e. constant value (e.g. radionuclide).
  map<string, string> specific_value;
};

#endif
