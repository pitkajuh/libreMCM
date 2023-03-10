/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef READCOMPARTMENTDEFINITION_H
#define READCOMPARTMENTDEFINITION_H

#include "../class/AllCompartmentAllInitialValuesHalfLife.h"

extern AllCompartmentAllInitialValuesHalfLife compartment_parameters_rt;
extern AllCompartmentAllInitialValuesHalfLife compartment_parameters;
string get_compartment_parameter_value(string parameter_wanted);
void read_compartment_def(string directory);

#endif
