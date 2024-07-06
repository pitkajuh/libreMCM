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
#include "../inc/namespace.h"

using namespace libremcm;

smap CreatePairMap(Pair pair)
{
  StringSplit split;
  smap map;
  map.reserve(pair.list.size());

  for(const auto&i: pair.list)
    {
      split=LineSplit(i);
      map[split.name]=split.value;
    }
  return map;
}
