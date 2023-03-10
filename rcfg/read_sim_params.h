/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef READSIMPARAMS_H
#define READSIMPARAMS_H

#include <string>

using std::string;

void read_sim_params(string directory);
extern int t_start;
extern int t_end;
extern int steps;

#endif
