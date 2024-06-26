/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <algorithm>
#include <unordered_map>
#include <string>
#include <vector>

using std::unordered_map;
using std::string;
using std::vector;
using std::find;
using InitialValues=unordered_map<string, string>;

void GetIv(const InitialValues iv, vector<string> *IvNames)
{
  for(const auto& [name, value]: iv) if(find(IvNames->begin(), IvNames->end(), name)==IvNames->end()) IvNames->emplace_back(name);
}

vector<string> CreateAllInitialValues(const unordered_map<string, InitialValues> &iv)
{
  // Parses through the initial values set by user in the text file. Creates a vector which contains all unique iv names. For example, if compartments A and B contains ivs a1, a2 and b1, b2 respectively, the vector would contain {a1, a2, b1, b2} in alphabetical order.
  vector<string> *IvNames=new vector<string>;
  for(auto i=iv.begin(); i!=iv.end(); i++) GetIv(i->second, IvNames);
  sort(IvNames->begin(), IvNames->end());
  vector<string> r=*IvNames;
  delete IvNames;
  return r;
}
