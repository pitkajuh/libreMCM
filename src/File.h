/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef FILE_H
#define FILE_H

#include <cstdint>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <map>
#include <string>
using std::string;

using std::map;
using std::cout;
using std::vector;
using std::pair;
using std::streampos;
using std::ifstream;

class File
{
protected:
  void EraseLine(string &line);
  map<uint16_t, string> GetSettings(const vector<string> &ivs, map<string, uint16_t> &nameMap);
  void AddLine(vector<string> &content, string &line);
  const bool LineCommented(const string &line);

  pair<streampos, vector<string>> ReadContentSub(ifstream &file, streampos from);

  pair<streampos, vector<string>> ReadContent(ifstream &file, streampos from, const string &findString, const unsigned size);

  void ReadFile(const string &fileName);

public:
  virtual streampos SA(ifstream &file, streampos from, const string &line)=0;
  File(){}
  virtual ~File(){}
};

#endif
