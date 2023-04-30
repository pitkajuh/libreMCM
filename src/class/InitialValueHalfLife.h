/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef INITIALVALUEHALFLIFE_H
#define INITIALVALUEHALFLIFE_H

#include <string>

using std::string;

class InitialValueHalfLife
{
 public:
  string initial_value_name;
  string initial_value;
  float half_life;
};

#endif
