/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <algorithm>
#include <iterator>
#include "../global/compartment_diagonal_v2.h"

using std::find;
using std::distance;

const int get_compartment_index(const string compartment_name)
{
  const int i=distance(compartment_diagonal_v2.begin(), find(compartment_diagonal_v2.begin(), compartment_diagonal_v2.end(), compartment_name));
  return i;
}
