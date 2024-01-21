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

const bool is_in_vector(const vector<string> vec, const string str_find)
{
  // Checks if a string is in a string of vectors and return true/false.
  bool rt=false;

  if(find(vec.begin(), vec.end(), str_find)!=vec.end())
    {
      rt=true;
    }

  return rt;
}

const bool is_in_vector_int(const vector<int> vec, const int str_find)
{
  bool rt=false;

  if(find(vec.begin(), vec.end(), str_find)!=vec.end())
    {
      rt=true;
    }

  return rt;
}
