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
#include <algorithm>
#include <stdexcept>
#include <vector>
#include "../inc/namespace.h"

using namespace libremcm;
using std::vector;

const bool IsNumerical(const string &s)
{
  // Checks whether the string s in a number. Returns true, if string is a valid number.
  bool r=true;

  try
    {
      const double d=std::stod(s);
      (void) d;
    }
  catch(const std::invalid_argument &i)
    {
      r=false;
    }
  return r;
}

const bool IsIn(const string &s, const SMap &f)
{
  return f.find(s)!=f.end();
}

const bool IsIn(const string &s, const std::vector<string> &f)
{
  return std::find(f.begin(), f.end(), s)!=f.end();
}
