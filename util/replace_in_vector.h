/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef REPLACEINVECTOR_H
#define REPLACEINVECTOR_H

#include <string>
#include <vector>

using std::string;
using std::vector;

vector<string> replace_in_vector(vector<string> fa, const string result, int index_replace_from, int index_replace_to);
vector<string> replace_in_vector2(vector<string> fa, const string result, int index_replace_from, int index_replace_to);

#endif
