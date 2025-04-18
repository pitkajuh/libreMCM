/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef FILE_H
#define FILE_H

#include <algorithm>
#include <fstream>
#include <iostream>
using std::cout;

class File
{
protected:
  void ReadContent(ifstream &file, streampos &from, const string &findString)
  {
    string line;
    file.seekg(from);

    while(getline(file, line) and line!="}")
      {
	line.erase(remove(line.begin(), line.end(), ' '), line.end());
	// line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
	if(line.size()==0) continue;
	else if(line==findString)
	  {
	    cout<<"ReadContent "<<line<<" "<<line.size()<<" "<<from<<'\n';
	    break;
	  }
      }
    from=file.tellg();
  }

  void ReadFile(const string &fileName, streampos &from)
  {
    string line;
    string linePrevious;
    ifstream file(fileName);
    file.seekg(from);

    while(getline(file, line))
      {
	line.erase(remove(line.begin(), line.end(), ' '), line.end());
	// line.erase(remove_if(line.begin(), line.end(), isspace), line.end());

	if(line.size()==0) continue;
	// else if(line.substr(0, 7)=="vertex:" and line.back()=='{')
	//   {
	//     // line=line.substr(0)
	//     cout<<line.size()<<'\n';
	//     line=line.substr(7, line.size()-1);
	//     cout<<line<<" "<<line.size()<<'\n';
	//   }
	else if(line.substr(0, 7)=="vertex:")
	  {
	    from+=line.size();
	    line=line.substr(7, line.size());
	    cout<<"vertex "<<line<<" "<<from<<'\n';
	    ReadContent(file, from, "values");
	    ReadContent(file, from, "edges");
	    cout<<"----------"<<'\n';
	  }
	else linePrevious=line;

	// if(line.size()==0) continue;
	// else if(line.back()=='{')
	//   {
	//     from+=linePrevious.size();

	//     if(line.size()>1)
	//       {
	// 	linePrevious=line.substr(0, line.size()-1);
	// 	from+=linePrevious.size();
	// 	// from+=line.size();
	// 	// cout<<"line.size()>1"<<'\n';
	//       }

	//     cout<<"Reading "<<linePrevious<<" "<<from<<'\n';
	//     ReadContent(file, from);
	//     cout<<" "<<'\n';
	//   }
	// else linePrevious=line;
      }
    from=file.tellg();
  }
public:
  File(){}
  virtual ~File(){}
};

class FileGraph: public File
{
public:
  FileGraph(const string &fileName, streampos &from)
  {
    ReadFile(fileName, from);
  }

  FileGraph(){}
  ~FileGraph(){}
};

#endif
