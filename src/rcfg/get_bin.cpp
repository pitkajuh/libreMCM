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

struct LinePosition
{
  string line;
  streampos position;
};

// const string ParseName(string line)
// {
//   const int size=line.size();
//   const int at=1+line.find("{");
//   if(size==at) line=line.substr(0, size-1);
//   return line;
// }

LinePosition Get(ifstream &f, const streampos from, const string find, ReadFile *ftype)
{
  string line;
  string line_prev;
  string result1;
  bool empty=false;
  bool stop=false;
  Type result;
  streampos pos;
  streampos pos_prev=0;
  LinePosition res;

  while(getline(f, line) and !stop)
    {
      line=ParseLine(line);
      empty=line.empty();

      if(!empty)
	{
	  // cout<<"line "<<line<<" "<<pos<<'\n';
	  result=ftype->GetFunction(f, line, find, line_prev);
	  // pos=result.position;

	  // result1=result.line;

	  // res.line=result1;
	  // res.position=pos;

	  stop=result.stop;
	  // pos_prev=f.tellg();
	  line_prev=line;
	}
    }
  pos=result.position;
  // cout<<"line "<<line<<" "<<pos<<'\n';
  result1=result.line;

  res.line=result1;
  res.position=pos;
  return res;
}

// void LineForward(ifstream &bin, streampos to)
// {
//   string line;
//   bin.seekg(to, bin.beg);
//   getline(bin, line);
//   to = bin.tellg();
//   bin.seekg(to, bin.beg);
// }

LinePosition GetPosition(ifstream &bin, const streampos from, const string find, ReadFile * ftype)
{
  bin.seekg(from, bin.beg);
  return Get(bin, from, find, ftype);
}

// string GetName(ifstream &bin, streampos from)
// {
//   string line;
//   bin.seekg(from, bin.beg);
//   getline(bin, line);
//   return ParseName(line);
// }

LinePosition  ReadSection(ifstream &bin, streampos from, const string section)
{
  ReadFile *type=new FName;
  ReadFile *typedata=new FData;
  LinePosition aa=GetPosition(bin, from, section, type);
  // string line=GetName(bin, aa);
  cout<<"RESULT "<<aa.line<<'\n';

  // aa=GetPosition(bin, from, "{", type);
  // cout<<"aa "<<aa<<" "<<'\n';
  // LineForward(bin, aa);
  // cout<<"aa "<<aa<<" "<<'\n';
  // cout<<"GET CONTENT "<<aa.position<<'\n';
  // LinePosition aa1=Get(bin, aa.position, "}", typedata);
  LinePosition aa1=GetPosition(bin, aa.position, "}", typedata);
  // cout<<"aa "<<aa<<" "<<'\n';
  delete type;
  delete typedata;
  return aa1;
}

void GetBin(const string directory)
{
  const string FILE_NAME=directory+"bin";
  ifstream bin(FILE_NAME);
  LinePosition aa=ReadSection(bin, 0, "{");
  cout<<"RESULT "<<aa.line<<'\n';
  cout<<" @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<'\n';
  aa=ReadSection(bin, aa.position, "{");
  // cout<<"RESULT "<<aa.line<<" "<<aa.position<<'\n';
  bin.close();
}

void GetSettings(const string directory)
{
  const string FILE_NAME=directory+"sim_params";
  ifstream bin(FILE_NAME);
  LinePosition aa=ReadSection(bin, 0, "{");
  cout<<"RESULT "<<aa.line<<'\n';
  bin.close();
}

void GetInitialValues(const string directory)
{
  const string FILE_NAME=directory+"compartments2";
  ifstream bin(FILE_NAME);
  LinePosition aa=ReadSection(bin, 0, "{");


  while(!bin.eof()) aa=ReadSection(bin, aa.position, "{");



//   ReadFile *type=new FName;

//   streampos aa=GetPosition(bin, 0, "{", type);
//   streampos b=bin.tellg();
//   string line=GetName(bin, aa);
//   streampos bb=aa-streampos(line.size());
//   cout<<"find compartment "<<aa<<" "<<line<<" "<<b<<" "<<bb<<'\n';
//   // getline(bin, line);
//   // streampos b=aa-streampos(line.size());
//   b=bin.tellg();
//   bb=aa-streampos(line.size());
//   // line=GetName(bin, aa);
//   cout<<"find compartment 2 "<<b<<" "<<line<<" "<<line.size()<<" "<<bb<<'\n';


//   // streampos aa=ReadSection(bin, 0, "{");
// // aa=ReadSection(bin, aa, "initial_values");


//   // aa=GetPosition(bin, aa, "{", type);


//   // cout<<"find { "<<aa<<" "<<line<<'\n';
//   // LineForward(bin, aa);
//   // getline(bin, line);
//   // aa=GetPosition(bin, aa, "{", type);
//   // cout<<aa<<" "<<line<<'\n';

//   // ReadFile *typedata=new FData;
//   // aa=Get(bin, aa, "}", typedata);
//   // cout<<aa<<" "<<line<<'\n';



//   // while(!bin.eof()) aa=ReadSection(bin, aa, "{");


  bin.close();
}
