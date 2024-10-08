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
#include "../inc/namespace.h"

using namespace libremcm;
using std::vector;
using InitialValues=SMap;
using DInitialValues=Map<string, double>;

const DInitialValues ParseIv(InitialValues ivs, const vector<string> &iv_names)
{
  DInitialValues ivs_sorted;
  ivs_sorted.reserve(iv_names.size());

  for(const auto &i: iv_names)
    {
      if(ivs.find(i)==ivs.end()) ivs_sorted[i]=0;
      else ivs_sorted[i]=std::stod(ivs[i]);
    }
  return ivs_sorted;
}

const Map<string, DInitialValues> ParseInitialValues(Map<string, InitialValues> &ivs, const vector<string> &iv_names)
{
  // Takes the iv Map and unique iv names as an input. Sorts the Map values alphabetically and initializes the values with zero, if it is not found in the Map. Also the values are changed from string to double.
  Map<string, DInitialValues> ivs_sorted;
  ivs_sorted.reserve(ivs.size());

  for(const auto &[name, iv]: ivs) ivs_sorted[name]=ParseIv(iv, iv_names);
  return ivs_sorted;
}
