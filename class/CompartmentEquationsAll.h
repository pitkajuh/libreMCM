/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef COMPARTMENTEQUATIONSALL_H
#define COMPARTMENTEQUATIONSALL_H

#include "EquationsAll.h"

using std::string;

class CompartmentEquationsAll
{
 public:
  string compartment;
  EquationsAll equations_add;
  EquationsAll equations_subtract;
};

#endif
