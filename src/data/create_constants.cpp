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
#include <iostream>
#include <unordered_map>

using std::ifstream;
using std::cout;
using std::unordered_map;

// void CreateConstants(Pair constants)
// {
//   StringSplit split("", "");
//   string name;
//   string value;
//   unordered_map<string, string> map;

//   for(const auto&i: constants.list)
//     {
//       split=LineSplit(i);
//       name=split.name;
//       value=split.value;
//       map[name]=value;
//     }
// }
