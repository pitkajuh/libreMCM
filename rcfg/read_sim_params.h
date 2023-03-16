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

void read_sim_params(const string directory);
extern double t_start;
extern double t_end;
extern double step_size;

#endif
