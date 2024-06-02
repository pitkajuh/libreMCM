/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../util/StringUtils.h"
#include "../types/ReadFile.h"
#include <unordered_map>

using std::unordered_map;

#include <iostream>

using std::ifstream;
using std::cout;
unordered_map<string, string> AddToMap(Pair pair, unordered_map<string, string> map)
{
  StringSplit split;

  for(const auto&i: pair.list)
    {
      split=LineSplit(i);
      map[split.name]=split.value;
    }
  return map;
}

unordered_map<string, string> CreatePairMap(Pair pair)
{
  StringSplit split;
  unordered_map<string, string> map;
  cout<<"COMPARTMENT "<<pair.name<<'\n';
  for(const auto&i: pair.list)
    {
      split=LineSplit(i);
      map[split.name]=split.value;
    }
  return map;
}
