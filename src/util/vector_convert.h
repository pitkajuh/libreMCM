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

const vector<string> equation_string_to_equation_vector2(const string equation);
const vector<string> equation_string_to_equation_vector(const string equation);
const string vector_to_string(const vector<string> vec);

#endif
