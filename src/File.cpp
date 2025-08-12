#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <map>
#include "File.h"
#include <string>
#include <cstdint>

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

map<uint16_t, string> File::GetSettings(const vector<string> &ivs, map<string, uint16_t> &nameMap)
{
  uint16_t n=0;
  map<uint16_t, string> result;

  for(const auto &iv: ivs)
    {
      const uint16_t at=iv.find("=");
      const string name=iv.substr(0, at);
      const string value=iv.substr(at+1, iv.size()-1);
      result[n]=value;
      nameMap[name]=n;
      n++;
    }
  return result;
}

void File::AddLine(vector<string> &content, string &line)
{
  while(line.size()>1)
    {
      const uint16_t at=line.find(";");
      content.emplace_back(line.substr(0, at));
      line.erase(line.begin(), line.begin()+at+1);
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
	  AddLine(content, line);
	}
    }
  return {file.tellg(), content};
}

pair<streampos, vector<string>> File::ReadContent(ifstream &file, streampos from, const string &findString, const uint16_t size)
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
