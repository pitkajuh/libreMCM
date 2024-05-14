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
  cout<<"RESULT1 "<<type->line<<'\n';
}

FileData RR(ifstream &bin, streampos from)
{
  FileData r;
  GetLine(bin, from, r.name, open);
  GetLine(bin, r.name->position, r.data, close);
  return r;
}

void GetBin(const string directory)
{
  const string FILE_NAME=directory+"bin";
  ifstream bin(FILE_NAME);

  FileData constants_new=RR(bin, 0);
  FileData equations_new=RR(bin, constants_new.data->position);
  cout<<"                  "<<'\n';
  bin.close();
}

void GetSettings(const string directory)
{
  const string FILE_NAME=directory+"sim_params";
  ifstream bin(FILE_NAME);
  FileData settings_new=RR(bin, 0);
  bin.close();
}

void GetInitialValues(const string directory)
{
  const string FILE_NAME=directory+"compartments2";
  ifstream bin(FILE_NAME);
  FileData compartment_new=RR(bin, 0);

  while(!bin.eof())  compartment_new=RR(bin, compartment_new.data->position);

  cout<<"aoea"<<'\n';
  bin.close();
}
