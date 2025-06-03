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
#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <map>
#include "FileSettings.h"

using std::map;
using std::cout;
using std::vector;
using std::pair;
using std::streampos;
using std::ifstream;

streampos FileSettings::SA(ifstream &file, streampos from, const string &line)
{
  pair<streampos, vector<string>> result;
  const string settings="simulation_settings";

  if(line.substr(0, 19)==settings)
    {
      result=ReadContent(file, from, settings, 19);
      set=GetSettings(result.second);
    }
  from=result.first;
  return from;
}

FileSettings::FileSettings(const string &fileName)
{
  ReadFile(fileName);
}
