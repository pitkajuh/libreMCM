/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <vector>
#include <string>

using std::string;
using std::vector;

const vector<string> combine_vectors(const vector<string> vec_from, vector<string> vec_to)
{
  vec_to.insert(vec_to.end(), vec_from.begin(), vec_from.end());
  return vec_to;
}
