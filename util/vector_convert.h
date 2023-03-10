/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef VECTORCONVERT_H
#define VECTORCONVERT_H

#include <string>
#include <vector>

using std::string;
using std::vector;

vector<string> equation_string_to_equation_vector(string equation);
string vector_to_string(vector<string> vec);

#endif
