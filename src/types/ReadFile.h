/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef READFILE_H
#define READFILE_H

#include <fstream>
#include <vector>
#include "StringSplit.h"
#include <unordered_map>

using std::unordered_map;
using std::ifstream;
using std::streampos;
using std::vector;
#include <iostream>
struct Type
{
  bool stop=false;
  streampos position;
  string line;

  void Set(const bool v1, const streampos v2, const string str)
  {
    stop=v1;
    position=v2;
    line=str;
  }
};

const string NameSelect(string now, const string prev)
{
  const int sizenow=now.size();
  const int at=1+now.find("{");

  if(sizenow==1 and now=="{") now=prev;
  else if(sizenow>1 and sizenow==at) now=now.substr(0, sizenow-1);

  return now;
}

class ReadFile
{
public:
  virtual Type GetFunction(ifstream &f, const string line, const string find, const string line_prev)=0;
};

class FName: public ReadFile
{
public:

  Type GetFunction(ifstream &f, const string line, const string find, const string line_prev)
  {
    const int size=line.size();
    const size_t  o=line.find(find);
    bool stop=false;
    streampos  read_pos;
    Type result;
    string newline;

    if(o<size)
      {
	read_pos = f.tellg()-streampos(size+1);
	stop=true;
	newline=NameSelect(line, line_prev);
	// std::cout<<"now "<<line<<" prev "<<line_prev<<'\n';
	// result.Set(stop, read_pos, newline);
      }
    result.Set(stop, read_pos, newline);
    return result;
  }
};

class FData: public ReadFile
{
public:
  // unordered_map<string, vector<string>> data;
  vector<StringSplit> test;

  void PushTo(const string line, const int size)
  {
    const size_t  o=line.find("=");

    if(size>1 and o<size)
      {
	StringSplit split=LineSplit(line);
	test.push_back(split);
	std::cout<<"TEST "<<test.size()<<" "<<line<<'\n';
      }
  }

  Type GetFunction(ifstream &f, const string line, const string find, const string line_prev)
  {
    const int size=line.size();
    const size_t  o=line.find(find);
    bool stop=false;
    streampos  read_pos;
    Type result;

    if(o<size)
      {
	read_pos = f.tellg();
	stop=true;
      }
    result.Set(stop, read_pos, line_prev);
    PushTo(line, size);

    return result;
  }
};

#endif
