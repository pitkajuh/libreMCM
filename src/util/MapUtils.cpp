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

unordered_map<string, string> CreatePairMap(Pair pair)
{
  StringSplit split;
  unordered_map<string, string> map;
  map.reserve(pair.list.size());

  for(const auto&i: pair.list)
    {
      split=LineSplit(i);
      map[split.name]=split.value;
    }
  return map;
}
