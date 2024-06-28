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
#include <algorithm>

using std::string;
using std::vector;
using std::find;

bool IsIn(const string &s, const vector<string> &f)
{
  return find(f.begin(), f.end(), s)!=f.end();
}
