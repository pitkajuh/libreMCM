/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef COMPARTMENTTOTALEQUATION_H
#define COMPARTMENTTOTALEQUATION_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class CompartmentTotalEquation
{
 public:
  string compartment_name;
  vector<string> total_equation;
};

#endif
