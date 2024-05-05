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

streampos Get(ifstream &f, const streampos from, const string find, ReadFile * ftype)
{
  string line;
  bool empty=false;
  bool stop=false;
  Type result;
  streampos pos;

  while(getline(f, line) and !stop)
    {
      line=ParseLine(line);
      empty=line.empty();

      if(!empty)
	{
	  result=ftype->GetFunction(f, line, find);
	  stop=result.stop;
	  pos=result.position;
	}
    }
  return pos;
}

const string ParseName(string line)
{
  const int size=line.size();
  const int at=1+line.find("{");
  if(size==at) line=line.substr(0, size-1);
  return line;
}

void LineForward(ifstream &bin, streampos to)
{
  string line;
  bin.seekg(to, bin.beg);
  getline(bin, line);
  to = bin.tellg();
  bin.seekg(to, bin.beg);
}

streampos GetPosition(ifstream &bin, const streampos from, const string find, ReadFile * ftype)
{
  bin.seekg(from, bin.beg);
  return Get(bin, from, find, ftype);
}

string GetName(ifstream &bin, streampos from)
{
  string line;
  bin.seekg(from, bin.beg);
  getline(bin, line);
  return ParseName(line);
}

streampos ReadSection(ifstream &bin, streampos from, const string section)
{
  ReadFile *type=new FName;
  ReadFile *typedata=new FData;
  streampos aa=GetPosition(bin, from, section, type);
  string line=GetName(bin, aa);
  cout<<"LINE "<<line<<" aa "<<aa<<'\n';
  aa=GetPosition(bin, from, "{", type);
  cout<<"aa "<<aa<<" "<<'\n';
  LineForward(bin, aa);
  cout<<"aa "<<aa<<" "<<'\n';
  aa=Get(bin, aa, "}", typedata);
  cout<<"aa "<<aa<<" "<<'\n';
  delete type;
  delete typedata;
  return aa;
}

void GetBin(const string directory)
{
  const string FILE_NAME=directory+"bin";
  ifstream bin(FILE_NAME);
  streampos aa=ReadSection(bin, 0, "constants");
  cout<<" @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<'\n';
  aa=ReadSection(bin, aa, "equations");
  bin.close();
}

void GetSettings(const string directory)
{
  const string FILE_NAME=directory+"sim_params";
  ifstream bin(FILE_NAME);
  streampos aa=ReadSection(bin, 0, "simulation_settings");
  bin.close();
}

streampos ReadCompartment(ifstream &bin, streampos from, const string section)
{
  streampos aa;

  return aa;
}

void GetInitialValues(const string directory)
{
  const string FILE_NAME=directory+"compartments2";
  ifstream bin(FILE_NAME);
  streampos aa=ReadSection(bin, 0, "{");
// aa=ReadSection(bin, aa, "initial_values");

  // ReadFile *type=new FName;

  // streampos aa=GetPosition(bin, 0, "{", type);
  // string line=GetName(bin, aa);
  // cout<<"find compartment "<<aa<<" "<<line<<'\n';

  // aa=GetPosition(bin, aa, "{", type);


  // cout<<"find { "<<aa<<" "<<line<<'\n';
  // LineForward(bin, aa);
  // getline(bin, line);
  // aa=GetPosition(bin, aa, "{", type);
  // cout<<aa<<" "<<line<<'\n';

  // ReadFile *typedata=new FData;
  // aa=Get(bin, aa, "}", typedata);
  // cout<<aa<<" "<<line<<'\n';



  while(!bin.eof()) aa=ReadSection(bin, aa, "{");


  bin.close();
}
