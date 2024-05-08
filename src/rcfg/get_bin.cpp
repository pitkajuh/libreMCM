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
#include <iostream>

using std::ifstream;
using std::cout;

// struct LinePosition
// {
//   string line;
//   streampos position;
// };

ReadFile *Get(ifstream &f, const streampos from, const string find, ReadFile *ftype)
{
  string line;
  string line_prev;
  string result1;
  bool empty=false;
  bool stop=false;
  ReadFile *result;

  while(getline(f, line) and !stop)
    {
      line=ParseLine(line);
      empty=line.empty();

      if(!empty)
	{
	  ftype=ftype->GetFunction(f, line, find, line_prev);
	  stop=ftype->stop;
	  line_prev=line;
	}
    }
  // result1=result.line;
  // res.line=result1;
  // res.position=result.position;
  // result->Set(stop, position, stop);
  return ftype;
}

ReadFile *GetPosition(ifstream &bin, const streampos from, const string find, ReadFile *ftype)
{
  bin.seekg(from, bin.beg);
  ftype=Get(bin, from, find, ftype);
  return ftype;
}

// LinePosition  ReadSection(ifstream &bin, streampos from)
// {
//   ReadFile *type=new FName;
//   ReadFile *typedata=new FData;
//   LinePosition aa=GetPosition(bin, from, "{", type);
//   cout<<"RESULT1 "<<aa.line<<'\n';
//   typedata=GetPosition(bin, aa.position, "}", typedata);
//   delete type;
//   delete typedata;
//   return aa1;
// }

ReadFile  *GetName(ifstream &bin, streampos from)
{
  ReadFile *type=new FName;
  type=GetPosition(bin, from, "{", type);
  // const string line=type->line;
  cout<<"RESULT1 "<<type->line<<'\n';
  // delete type;
  return type;
}

LinePosition  ReadSection(ifstream &bin, streampos from)
{
  ReadFile *type=new FName;
  ReadFile *typedata=new FData;
  LinePosition aa=GetPosition(bin, from, "{", type);
  cout<<"RESULT1 "<<aa.line<<'\n';
  typedata=GetPosition(bin, aa.position, "}", typedata);
  delete type;
  delete typedata;
  return aa1;
}

void GetBin(const string directory)
{
  const string FILE_NAME=directory+"bin";
  ifstream bin(FILE_NAME);
  LinePosition aa=ReadSection(bin, 0);
  cout<<" @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<'\n';
  aa=ReadSection(bin, aa.position);
  bin.close();
}

void GetSettings(const string directory)
{
  const string FILE_NAME=directory+"sim_params";
  ifstream bin(FILE_NAME);
  LinePosition aa=ReadSection(bin, 0);
  bin.close();
}

void GetInitialValues(const string directory)
{
  const string FILE_NAME=directory+"compartments2";
  ifstream bin(FILE_NAME);
  LinePosition aa=ReadSection(bin, 0);

  while(!bin.eof()) aa=ReadSection(bin, aa.position);

  bin.close();
}
