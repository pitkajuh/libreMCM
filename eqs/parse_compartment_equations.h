/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef PARSECOMPARTMENTEQUATIONS_H
#define PARSECOMPARTMENTEQUATIONS_H

#include "../class/CompartmentEquationsAddSubtractAll.h"
#include "../class/EquationsAddSubtractAll.h"
#include "../class/AllCompartmentInitialValuesHalfLife.h"

extern CompartmentEquationsAddSubtractAll equations_with_compartment_name;
extern AllCompartmentInitialValuesHalfLife all_values;
extern EquationsAddSubtractAll rt_local_global;
AllCompartmentInitialValuesHalfLife parse_compartment_equations_subsubroutine();
void parse_compartment_equations_subroutine();
void parse_compartment_equations();

#endif
