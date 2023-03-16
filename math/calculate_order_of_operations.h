/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef CALCULATEORDEROFOPERATIONS_H
#define CALCULATEORDEROFOPERATIONS_H

#include <string>
#include <vector>

using std::string;
using std::vector;

vector<string> calculate_order_of_operations2(vector<string> fa);
vector<string> do_calculation(vector<string> fa, const int index);

#endif
