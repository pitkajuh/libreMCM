/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

using std::unordered_map;
using std::string;
using std::vector;
using std::find;
using std::cout;
using std::stod;
using InitialValues=unordered_map<string, string>;
using DInitialValues=unordered_map<string, double>;

DInitialValues ParseIv(InitialValues ivs, const vector<string> &iv_names)
{
  DInitialValues ivs_sorted;
  ivs_sorted.reserve(iv_names.size());

  for(const auto &i: iv_names)
    {
      if(ivs.find(i)==ivs.end()) ivs_sorted[i]=0;
      else  ivs_sorted[i]=stod(ivs[i]);
    }
  return ivs_sorted;
}

unordered_map<string, DInitialValues> ParseInitialValues(unordered_map<string, InitialValues> &ivs, const vector<string> &iv_names)
{
  // Takes the iv map and unique iv names as an input. Sorts the map values alphabetically and initializes the values with zero, if it is not found in the map. Also the values are changed from string to double.
  unordered_map<string, DInitialValues> ivs_sorted;
  ivs_sorted.reserve(ivs.size());

  for(const auto &[name, iv]: ivs) ivs_sorted[name]=ParseIv(iv, iv_names);
  return ivs_sorted;
}
