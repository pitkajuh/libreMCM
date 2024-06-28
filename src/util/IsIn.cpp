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
#include <unordered_map>

using std::string;
using std::vector;
using std::find;
using std::unordered_map;

bool IsIn(const string &s, const unordered_map<string, string> &f)
{
  return f.find(s)!=f.end();
}

bool IsIn(const string &s, const vector<string> &f)
{
  return find(f.begin(), f.end(), s)!=f.end();
}
