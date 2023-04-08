/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../class/SplittedString.h"

const SplittedString string_split(const string str, const string splitter)
{
  const int size=str.size();
  const int split_at=str.find(splitter);
  const int to=size-split_at-2;
  const string part1=str.substr(0, split_at);
  const string part2=str.substr(split_at+1, to);
  SplittedString result;
  result.splitted_string_part1=part1;
  result.splitted_string_part2=part2;
  return result;
}
