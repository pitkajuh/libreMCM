/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef TEST_H
#define TEST_H

#include "../types/MathOperation.h"
#include "../types/Graph.h"

vector<string> test(vector<string> equation, uint8_t &id, const vector<string> &data, GraphEquation *&graph);
vector<string> Remove(vector<string> equation, const uint8_t open, const uint8_t close);

#endif
