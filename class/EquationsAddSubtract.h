/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef EQUATIONSADDSUBTRACT_H
#define EQUATIONSADDSUBTRACT_H

#include "Equations.h"

class EquationsAddSubtract
{
 public:
  string compartment;
  bool add_equations;
  Equations equations;
};

#endif
