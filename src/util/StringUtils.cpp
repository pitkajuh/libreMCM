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

  // Line is commented in the beginning.
  if(comment==COMMENT) line="";
  else
    {
      const int at=distance(line.begin(), find(line.begin(), line.end(), '/'));
      if(line[at]=='/' and line[at+1]=='/') line=line.substr(0, at);
    }
  return line;
}

StringSplit LineSplit(string line)
{
  const int SIZE=line.size();
  const int at=distance(line.begin(), find(line.begin(), line.end(), '='));
  string name="";
  string value="";

  if(at!=SIZE and line.back()==';')
    {
      name=line.substr(0, at);
      value=line.substr(at+1, line.size());

      std::cout<<"name "<<name<<" value "<<value<<'\n';
    }
  StringSplit r;
  r.name=name;
  r.value=value;
  return r;
}

const string ParseLine(string line)
{
  line.erase(remove(line.begin(), line.end(), ' '), line.end());
  // std::cout<<"size "<<line.size()<<'\n';
  line=RemoveComment(line);
  // LineSplit(line);
  return line;
}
