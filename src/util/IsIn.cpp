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
#include <stdexcept>

using std::string;

bool IsNumerical(const string &s)
{
  // Checks whether the string s in a number. Returns true, if string is a valid number.
  bool r=true;

  try
    {
      const double d=std::stod(s);
    }
  catch(const std::invalid_argument &i)
    {
      r=false;
    }
  return r;
}

bool IsIn(const string &s, const std::unordered_map<string, string> &f)
{
  return f.find(s)!=f.end();
}

bool IsIn(const string &s, const std::vector<string> &f)
{
  return std::find(f.begin(), f.end(), s)!=f.end();
}
