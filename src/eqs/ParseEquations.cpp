/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

// #include "../types/Csv.h"
// #include "../types/AddSubtract.h"
#include <unordered_map>
#include <string>

using std::unordered_map;
using std::string;

void ParseEquations(const unordered_map<string, string> equations_map)
{
  string name;
  string equation;

  for(auto i=equations_map.begin(); i!=equations_map.end(); i++)
    {
      name=i->first;
      equation=i->second;
    }
}
