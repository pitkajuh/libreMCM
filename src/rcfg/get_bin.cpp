/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../util/StringUtils.h"
#include "../types/ReadFile.h"
#include "../util/MapUtils.h"
#include <iostream>

using std::ifstream;
using std::cout;

const string open="{";
const string close="}";

void Get(ifstream &f, const streampos from, const string find, ReadFile *ftype)
{
  string line;
  string line_prev;
  bool empty=false;
  bool stop=false;

  while(getline(f, line) and !stop)
    {
      line=ParseLine(line);
      empty=line.empty();

      if(!empty)
	{
	  ftype->GetFunction(f, line, find, line_prev, ftype);
	  stop=ftype->stop;
	  line_prev=line;
	}
    }
}

void GetLine(ifstream &bin, streampos from, ReadFile *type, const string find)
{
  bin.seekg(from, bin.beg);
  Get(bin, from, find, type);
}

FileData Read(ifstream &bin, streampos from)
{
  FileData r;
  GetLine(bin, from, r.name, open);
  GetLine(bin, r.name->position, r.data, close);
  return r;
}

Pair GetData(ifstream &bin, streampos from)
{
  const FileData result=Read(bin, from);
  const Pair r(result.name->line, result.data->v, result.data->position);
  return r;
}

const unordered_map<string, string> GetBin(ifstream &bin, streampos *from)
{
  const Pair pair=GetData(bin, *from);
  const unordered_map<string, string> map=CreatePairMap(pair);
  *from=pair.position;
  return map;
}

void GetInitialValues(const string directory)
{
  // const string FILE_NAME=directory+"compartments2";
  // ifstream bin(FILE_NAME);
  // FileData compartment=Read(bin, 0);

  // while(!bin.eof())  compartment=Read(bin, compartment.data->position);

  // bin.close();
  ifstream compartments(directory+"compartments");
  from=new streampos;
  *from=0;
}
