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

// void Get(ifstream &f, const streampos from, const string find, ReadFile *ftype)
// {
//   string line;
//   string line_prev;
//   bool empty=false;
//   bool stop=false;
//   // ReadFile *result=ftype;

//   while(getline(f, line) and !stop)
//     {
//       line=ParseLine(line);
//       empty=line.empty();

//       if(!empty)
// 	{
// 	  // ftype->GetFunction(f, line, find, line_prev, ftype);
// 	  stop=ftype->stop;
// 	  // result=result->GetFunction(f, line, find, line_prev);
// 	  // // result->PushTo();
// 	  // stop=result->stop;
// 	  line_prev=line;
// 	}
//     }
//   // return ftype;
//   // return result;
// }

// void GetPosition(ifstream &bin, const streampos from, const string find, ReadFile *ftype)
// {
//   bin.seekg(from, bin.beg);
//   Get(bin, from, find, ftype);
//   // return ftype;
// }

// // LinePosition  ReadSection(ifstream &bin, streampos from)
// // {
// //   ReadFile *type=new FName;
// //   ReadFile *typedata=new FData;
// //   LinePosition aa=GetPosition(bin, from, "{", type);
// //   cout<<"RESULT1 "<<aa.line<<'\n';
// //   typedata=GetPosition(bin, aa.position, "}", typedata);
// //   delete type;
// //   delete typedata;
// //   return aa1;
// // }

// void GetName(ifstream &bin, streampos from, ReadFile *type)
// {
//   // ReadFile *type=new FName;
// GetPosition(bin, from, "{", type);
//   // const string line=type->line;
//   cout<<"RESULT1 "<<type->line<<'\n';
//   // delete type;
//   // return type;
// }

// ReadFile  *GetContent(ifstream &bin, streampos from, ReadFile *type)
// {
//   // ReadFile *type=new FData;
//   GetPosition(bin, from, "}", type);
//   // const string line=type->line;
//   cout<<"RESULT1 "<<type->line<<'\n';
//   // delete type;
//   return type;
// }

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

void GetBin(const string directory)
{
  const string FILE_NAME=directory+"bin";
  ifstream bin(FILE_NAME);

  ReadFile *constants=new FName;
  // GetName(bin, 0, constants);

  // ReadFile *constants_content=new FData;
  // GetName(bin, constants->position, constants_content);

  // ReadFile *constants=GetName(bin, 0);
  // ReadFile *constants_content=GetContent(bin, constants->position);

  // constants_content->Clear();
  // LinePosition aa=ReadSection(bin, 0);
  cout<<" @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<'\n';
  //   ReadFile *equations=GetName(bin, constants_content->position);
  // ReadFile *equations_content=GetContent(bin, equations->position);


  // aa=ReadSection(bin, aa.position);
  // delete constants;
  // delete constants_content;
  //   delete equations;
  // delete equations_content;
  bin.close();
}

void GetSettings(const string directory)
{
  // const string FILE_NAME=directory+"sim_params";
  // ifstream bin(FILE_NAME);
  // LinePosition aa=ReadSection(bin, 0);
  // bin.close();
}

void GetInitialValues(const string directory)
{
  // const string FILE_NAME=directory+"compartments2";
  // ifstream bin(FILE_NAME);
  // LinePosition aa=ReadSection(bin, 0);

  // while(!bin.eof()) aa=ReadSection(bin, aa.position);

  // bin.close();
}
