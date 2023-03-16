/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef TARGETCOMPARTMENTS_H
#define TARGETCOMPARTMENTS_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class TargetCompartments
{
 public:
  vector<string> add_to_compartments;
  vector<string> subtract_from_compartments;
};

#endif
