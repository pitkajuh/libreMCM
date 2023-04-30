/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef ISINVECTORF_H
#define ISINVECTORF_H

#include <string>
#include <vector>

using std::string;
using std::vector;

const bool is_in_vector(const vector<string> vec, const string str_find);
const bool is_in_vector_int(const vector<int> vec, const int str_find);
#endif
