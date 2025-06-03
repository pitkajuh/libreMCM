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
#include "File.h"
#include <string>
using std::string;

using std::map;
using std::cout;
using std::vector;
using std::pair;
using std::streampos;
using std::ifstream;

void File::EraseLine(string &line)
{
  line.erase(remove(line.begin(), line.end(), ' '), line.end());
}

map<string, string> File::GetSettings(const vector<string> &ivs)
{
  string name;
  string value;
  map<string, string> result;

  for(const auto &iv: ivs)
    {
      const unsigned at=iv.find("=");
      name=iv.substr(0, at);
      value=iv.substr(at+1, iv.size()-1);
      result[name]=value;
    }
  return result;
}

void File::AddLine(vector<string> &content, string &line)
{
  while(line.size()>1)
    {
      const unsigned at=line.find(";");
      content.emplace_back(line.substr(0, at));
      line.erase(line.begin(), line.begin()+at+1);
      // cout<<"TEST "<<line<<'\n';
    }
}

const bool File::LineCommented(const string &line){return line[0]=='/' and line[1]=='/';}

pair<streampos, vector<string>> File::ReadContentSub(ifstream &file, streampos from)
{
  string line;
  vector<string> content;
  file.seekg(from);

  while(getline(file, line))
    {
      EraseLine(line);
      if(line.size()==0 or line=="{" or LineCommented(line)) continue;
      else if(line=="}") break;
      else
	{
	  cout<<line<<'\n';
	  // content.emplace_back(line);
	  AddLine(content, line);
	}
    }
  return {file.tellg(), content};
}

pair<streampos, vector<string>> File::ReadContent(ifstream &file, streampos from, const string &findString, const unsigned size)
{
  string line;
  pair<streampos, vector<string>> result;
  file.seekg(from);

  while(getline(file, line))
    {
      EraseLine(line);

      if(line.size()==0 or LineCommented(line)) continue;
      else if(line.substr(0, size)==findString or line==findString+"{")
	{
	  result=ReadContentSub(file, file.tellg());
	  break;
	}
    }
  return result;
}

void File::ReadFile(const string &fileName)
{
  streampos from=0;
  string line;
  ifstream file(fileName);
  file.seekg(from);

  while(getline(file, line))
    {
      EraseLine(line);

      if(line.size()==0 or LineCommented(line)) continue;
      from=SA(file, from, line);
    }

  file.close();
}
