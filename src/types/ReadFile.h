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
  string line;

  void Set(const bool v1, const streampos v2, const string str)
  {
    stop=v1;
    position=v2;
    line=str;
  }
};

class ReadFile
{
public:

  virtual Type GetFunction(ifstream &f, const string line, const string find, string str_prev)=0;
};

class FName: public ReadFile
{
public:

  Type GetFunction(ifstream &f, const string line, const string find, string str_prev)
  {
    const int size=line.size();
    bool stop=false;
    size_t  o=line.find(find);
    streampos  read_pos;
    Type result;
    // cout<<read_pos<<" "<<find<<" "<<from<<" "<<o<<"/"<<size<<" "<<read_pos<<" "<<line<<'\n';

    std::cout<<"now :"<<line<<" prev "<<str_prev<<": "<<'\n';
    //   }

    // std::cout<<"size "<<size<<" :"<<line<<": o "<<o<<'\n';
    // std::cout<<o<<"<"<<size<<'\n';
    if(o<size)
    // if(o!=size)
      {
	read_pos = f.tellg()-streampos(size+1);
	// read_pos = f.tellg();
	// read_pos = pos_prev;

	// getline(f, line2);

	// std::cout<<"now "<<read_pos<<" "<<line2<<'\n';
	// read_pos = f.tellg();
	// cout<<"STOP "<<line<<'\n';




	stop=true;
	result.Set(stop, read_pos, str_prev);
	// cout<<"STOP "<<read_pos<<" "<<find<<" "<<from<<" "<<o<<"/"<<size<<" "<<read_pos<<" "<<line<<'\n';
	// break;
      }
    std::cout<<"   "<<'\n';
    return result;
  }
};

class FData: public ReadFile
{
public:

  Type GetFunction(ifstream &f, const string line, const string find, string str_prev)
  {
    const int size=line.size();
    bool stop=false;
    size_t  o=line.find(find);
    streampos  read_pos;
    Type result;
    StringSplit split;
    // cout<<read_pos<<" "<<find<<" "<<from<<" "<<o<<"/"<<size<<" "<<read_pos<<" "<<line<<'\n';

    if(o<size)
      {
	read_pos = f.tellg();
	// cout<<read_pos<<" "<<find<<" "<<from<<" "<<o<<"/"<<size<<" "<<read_pos<<" "<<line<<'\n';
	stop=true;
	result.Set(stop, read_pos, str_prev);
      }
    split=LineSplit(line);
    return result;
  }
};

#endif
