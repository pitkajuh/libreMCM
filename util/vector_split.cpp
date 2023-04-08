/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <string>
#include <vector>

using std::string;
using std::vector;

const vector<string> vector_split(const vector<string> fa, const int start, const int stop)
{
  const vector<string> rt (fa.begin()+start, fa.begin()+stop+1);
  return rt;
}
