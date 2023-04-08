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

#include <string>

using std::string;

void read_compartment_def(const string directory);
void parse_initial_values();

#endif
