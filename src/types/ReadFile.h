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
#include <memory>
#include "StringSplit.h"
#include "../global/mathconst.h"

using std::ifstream;
using std::streampos;
using std::vector;

class ReadFile
{
public:
  bool stop=false;
  streampos position=0;
  string line;

  virtual void GetFunction(ifstream &f, const string line, const string find, const string previous, ReadFile *res)=0;
  virtual void PushTo(){}

  void Set(const bool &v1, const streampos &v2, const string str)
  {
    stop=v1;
    position=v2;
    line=str;
  }

  const string SelectName(string now, const string prev)
  {
    const unsigned sizenow=now.size();
    const unsigned at=1+now.find(BOPEN);

    if(sizenow==1 and now==BOPEN) now=prev;
    else if(sizenow>1 and sizenow==at) now=now.substr(0, sizenow-1);

    return now;
  }
};

class FName: public ReadFile
{
public:
  void GetFunction(ifstream &f, const string line, const string find, const string previous, ReadFile *res)
  {
    const unsigned size=line.size();
    const size_t o=line.find(find);
    bool stop=false;
    streampos read_pos;
    string newline;

    if(o<size)
      {
	read_pos = f.tellg()-streampos(size+1);
	stop=true;
	newline=SelectName(line, previous);
      }
    res->Set(stop, read_pos, newline);
  }
};

class FData: public ReadFile
{
public:
  vector<string> v;

  void PushTo()
  {
    const unsigned size=line.size();
    const size_t o=line.find(EQUAL);

    if(size>1 and o<size) v.emplace_back(line);
  }

  void GetFunction(ifstream &f, const string line, const string find, const string previous, ReadFile *res)
  {
    const unsigned size=line.size();
    const size_t o=line.find(find);
    bool stop=false;
    streampos read_pos;

    if(o<size)
      {
	read_pos = f.tellg();
	stop=true;
      }
    res->Set(stop, read_pos, previous);
    res->PushTo();
  }
};

class FileData
{
public:
  ReadFile *name=new FName;
  FData *data=new FData;

  FileData()=default;

  FileData(const FileData &d)
  {
    name=d.name;
    data=d.data;
  }

  FileData& operator =(const FileData &d){return *this;}

  ~FileData()
  {
    delete name;
    delete data;
  }
};

struct Pair
{
  string name;
  vector<string> list;
  streampos position;

  Pair(const string s, const vector<string> &v, const unsigned p)
  {
    name=s;
    list=v;
    position=p;
  }
};

#endif
