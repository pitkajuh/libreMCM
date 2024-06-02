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

void GetIv(const InitialValues iv,  vector<string> *IvNames)
{
    for(auto i=iv.begin(); i!=iv.end(); i++)  if(find(IvNames->begin(), IvNames->end(), i->first)==IvNames->end())  IvNames->push_back(i->first);
}

vector<string> CreateAllInitialValues(const unordered_map<string, InitialValues> iv)
{
  vector<string> *IvNames=new vector<string>;
  for(auto i=iv.begin(); i!=iv.end(); i++) GetIv(i->second, IvNames);
  sort(IvNames->begin(), IvNames->end());
  vector<string> r=*IvNames;
  delete IvNames;
  return r;
}
