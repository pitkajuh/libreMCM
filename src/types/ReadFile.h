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
#include "StringSplit.h"

using std::ifstream;
using std::streampos;
#include <iostream>
struct Type
{
  bool stop=false;
  streampos position;

  void Set(const bool v1, const streampos v2)
  {
    stop=v1;
    position=v2;
  }
};

class ReadFile
{
public:

  virtual Type GetFunction(ifstream &f, const string line, const string find)=0;
};

class FName: public ReadFile
{
public:

  Type GetFunction(ifstream &f, const string line, const string find)
  {
    const int size=line.size();
    bool stop=false;
    size_t  o=line.find(find);
    streampos  read_pos;
    Type result;
    // cout<<read_pos<<" "<<find<<" "<<from<<" "<<o<<"/"<<size<<" "<<read_pos<<" "<<line<<'\n';
    // std::cout<<"size "<<size<<" "<<line<<'\n';
    if(o<size or o==size)
      {
	read_pos = f.tellg()-streampos(size+1);
	// cout<<"STOP "<<line<<'\n';
	stop=true;
	result.Set(stop, read_pos);
	// cout<<"STOP "<<read_pos<<" "<<find<<" "<<from<<" "<<o<<"/"<<size<<" "<<read_pos<<" "<<line<<'\n';
	// break;
      }
    return result;
  }
};

class FData: public ReadFile
{
public:

  Type GetFunction(ifstream &f, const string line, const string find)
  {
    const int size=line.size();
    bool stop=false;
    size_t  o=line.find(find);
    streampos  read_pos;
    Type result;
    StringSplit split;
    // cout<<read_pos<<" "<<find<<" "<<from<<" "<<o<<"/"<<size<<" "<<read_pos<<" "<<line<<'\n';

    if(o<size or o==size)
      {
	read_pos = f.tellg();
	// cout<<read_pos<<" "<<find<<" "<<from<<" "<<o<<"/"<<size<<" "<<read_pos<<" "<<line<<'\n';
	stop=true;
	result.Set(stop, read_pos);
      }
    split=LineSplit(line);
    return result;
  }
};

#endif
