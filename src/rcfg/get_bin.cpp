/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../types/ReadFile.h"
#include "../util/StringUtils.h"
#include "../util/MapUtils.h"
#include "../inc/namespace.h"

using namespace libremcm;
using InitialValues=SMap;

void Get(ifstream &f, const streampos &from, const string &find, ReadFile *ftype)
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

void GetLine(ifstream &bin, streampos &from, ReadFile *type, const string &find)
{
  bin.seekg(from, bin.beg);
  Get(bin, from, find, type);
}

const FileData Read(ifstream &bin, streampos &from)
{
  FileData r;
  GetLine(bin, from, r.name, "{");
  GetLine(bin, r.name->position, r.data, "}");
  return r;
}

const Pair GetData(ifstream &bin, streampos &from)
{
  const FileData result=Read(bin, from);
  const Pair r(result.name->line, result.data->v, result.data->position);
  return r;
}

const SMap GetBin(ifstream &bin, streampos *from, string *name=nullptr)
{
  const Pair pair=GetData(bin, *from);

  if(name!=nullptr) *name=pair.name;
  const SMap Map=CreatePairMap(pair);
  *from=pair.position;
  return Map;
}

const Map<string, InitialValues> GetInitialValues(ifstream &bin)
{
  Map<string, InitialValues> Map;
  string *name=new string;
  streampos *from=new streampos;
  *from=0;

  while(!bin.eof()) Map[*name]=GetBin(bin, from, name);
  delete name;
  delete from;
  return Map;
}

const SMap GetMap(ifstream &bin, streampos *from=nullptr)
{
  SMap Map;

  if(from==nullptr)
    {
      from=new streampos;
      *from=0;
      Map=GetBin(bin, from);
      delete from;
    }
  else Map=GetBin(bin, from);
  return Map;
}
