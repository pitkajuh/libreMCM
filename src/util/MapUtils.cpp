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

const SMap CreatePairMap(const Pair &pair)
{
  StringSplit split;
  SMap Map;
  Map.reserve(pair.list.size());

  for(const auto&i: pair.list)
    {
      split=LineSplit(i);
      Map[split.name]=split.value;
    }
  return Map;
}
