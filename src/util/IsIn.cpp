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
#include <iostream>
#include <stdexcept>

using std::string;
using std::vector;
using std::unordered_map;

bool IsNumerical(const string &s)
{
  // Checks whether there are numbers(0-9) in the equations, not only constants and variables. Returns true, if string is a valid number.
  // const string str="^(-?)(0|([1-9][0-9]*))(\\.[0-9]+)?$";
  bool r=true;
  double d;

  try
    {
      d=std::stod(s);
    }
  catch(const std::invalid_argument &i)
    {
      r=false;
    }
  // for(const auto &i: s)
  //   {

  //   }
  return r;
}


bool IsIn(const string &s, const unordered_map<string, string> &f)
{
  return f.find(s)!=f.end();
}

bool IsIn(const string &s, const vector<string> &f)
{
  return std::find(f.begin(), f.end(), s)!=f.end();
}
