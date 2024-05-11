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

void GetBin(const string directory)
{
  const string FILE_NAME=directory+"bin";
  ifstream bin(FILE_NAME);

  ReadFile *constants=new FName;
  GetLine(bin, 0, constants, "{");
  FData *constants_content=new FData;
  GetLine(bin, constants->position, constants_content, "}");
  cout<<constants_content->test.size()<<'\n';

  ReadFile *equations=new FName;
  GetLine(bin, 0, equations, "{");
  FData *equations_content=new FData;
  GetLine(bin, equations->position, equations_content, "}");
  cout<<equations_content->test.size()<<'\n';

  delete constants;
  delete constants_content;
  delete equations;
  delete equations_content;
  bin.close();
}

void GetSettings(const string directory)
{
  const string FILE_NAME=directory+"sim_params";
  ifstream bin(FILE_NAME);

  ReadFile *settings=new FName;
  GetLine(bin, 0, settings, "{");
  FData *settings_content=new FData;
  GetLine(bin, settings->position, settings_content, "}");
  cout<<settings_content->test.size()<<'\n';

  delete settings;
  bin.close();
}

void GetInitialValues(const string directory)
{
  const string FILE_NAME=directory+"compartments2";
  ifstream bin(FILE_NAME);

  ReadFile *compartments=new FName;
  GetLine(bin, 0, compartments, "{");
  FData *compartments_content=new FData;
  GetLine(bin, compartments->position, compartments_content, "}");
  cout<<compartments_content->test.size()<<'\n';
  bin.close();
}
