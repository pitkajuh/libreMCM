/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef COMPARTMENTEQUATIONSADDSUBTRACT_H
#define COMPARTMENTEQUATIONSADDSUBTRACT_H

#include "Equations.h"

class CompartmentEquationsAddSubtract
{
 public:
  string compartment;
  Equations equations_add;
  Equations equations_subtract;
};

#endif
