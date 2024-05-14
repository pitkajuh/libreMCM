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
#include <memory>

using std::unordered_map;
using std::ifstream;
using std::streampos;
using std::vector;
#include <iostream>

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
  bool stop=false;
  streampos position=0;
  string line;

  virtual void GetFunction(ifstream &f, const string line, const string find, const string line_prev, ReadFile *res)=0;
  virtual void PushTo(){}

  void Set(const bool v1, const streampos v2, const string str)
  {
    stop=v1;
    position=v2;
    line=str;
  }
};

class FName: public ReadFile
{
public:
  void GetFunction(ifstream &f, const string line, const string find, const string line_prev, ReadFile*res)
  {
    const int size=line.size();
    const size_t  o=line.find(find);
    bool stop=false;
    streampos  read_pos;
    string newline;

    if(o<size)
      {
	read_pos = f.tellg()-streampos(size+1);
	stop=true;
	newline=NameSelect(line, line_prev);
      }
    res->Set(stop, read_pos, newline);
  }
};

class FData: public ReadFile
{
public:
  vector<StringSplit> test;

  void PushTo()
  {
    const int size=line.size();
    const size_t  o=line.find("=");

    if(size>1 and o<size)
      {
	StringSplit split=LineSplit(line);
	test.push_back(split);
	std::cout<<"TEST "<<test.size()<<" "<<line<<'\n';
      }
  }

  void GetFunction(ifstream &f, const string line, const string find, const string line_prev, ReadFile *res)
  {
    const int size=line.size();
    const size_t  o=line.find(find);
    bool stop=false;
    streampos  read_pos;

    if(o<size)
      {
	read_pos = f.tellg();
	stop=true;
      }
    res->Set(stop, read_pos, line_prev);
    res->PushTo();
  }
};

class FileData
{
public:
  ReadFile *name=new FName;
  FData *data=new FData;

  FileData(){}

  FileData(FileData& d)
  {
    name=new FName;
    data=new FData;
    name=d.name;
    data=d.data;
  }

  FileData& operator =(const FileData& d)
  {
    if(this == &d)
      {
	return *this;
      }
    return *this;
  }

  ~FileData()
  {
    delete name;
    delete data;
  }
};

#endif
