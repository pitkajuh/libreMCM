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
#include <iostream>
#include "../types/StringSplit.h"

using std::distance;
using std::find;

const string RemoveComment(string line)
{
  const string COMMENT="//";
  const string comment=line.substr(0, 2);

  if(comment==COMMENT) line="";
  else
    {
      const unsigned at=distance(line.begin(), find(line.begin(), line.end(), '/'));
      if(line[at]=='/' and line[at+1]=='/') line=line.substr(0, at);
    }

  return line;
}

StringSplit LineSplit(const string &line)
{
  const unsigned SIZE=line.size();
  const unsigned at=distance(line.begin(), find(line.begin(), line.end(), '='));
  string name;
  string value;

  if(at!=SIZE and line.back()==';')
    {
      name=line.substr(0, at);
      value=line.substr(at+1, SIZE-1);
      value.pop_back();
    }
  else
    {
      // What here?
    }

  return {name, value};
}

const string ParseLine(string &line)
{
  line.erase(remove(line.begin(), line.end(), ' '), line.end());
  return RemoveComment(line);
}
