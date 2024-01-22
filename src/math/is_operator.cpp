/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../global/global_constants.h"
#include "../util/is_in_vector.h"

const bool is_operator(const string elem)
{
  const vector<string> ops{ADD, SUBTRACT, MULTIPLY, DIVIDE, OPEN, CLOSE};
  return is_in_vector(ops, elem);
}
