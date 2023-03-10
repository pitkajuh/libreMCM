/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef PARSECOMPARTMENTEQSFORNUMCALC_H
#define PARSECOMPARTMENTEQSFORNUMCALC_H

#include "../class/CompartmentEquationsAddSubtractAll.h"

void parse_compartment_eqs_for_num_calc();
void get_equations_for_numerical_calculation();
extern CompartmentEquationsAddSubtractAll final_equations_for_calculation;
extern Equations equations_add_all;
extern Equations equations_subtract_all;

#endif
