/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef COMBINEVECTORS_H
#define COMBINEVECTORS_H

#include <string>
#include <vector>

using std::string;
using std::vector;

vector<string> combine_vectors(vector<string> vec1, int vec1_from, int vec1_to, vector<string> vec2);
vector<string> combine_vectors2(vector<string> vec_from, vector<string> vec2_to);

#endif
