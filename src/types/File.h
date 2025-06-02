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
  void EraseLine(string &line)
  {
    line.erase(remove(line.begin(), line.end(), ' '), line.end());
    // line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
  }

  // string SplitLine(string line)
  // {
  //   const uint8_t delimiterAt=distance();
  //   return "";
  // }

  void ReadInitialValues(ifstream &file, streampos &from)
  {
    string line;
    file.seekg(from);

    while(getline(file, line))
      {
	EraseLine(line);
	if(line.size()==0 or line=="{") continue;
	else if(line=="}") break;
	else cout<<"ReadInitialValues "<<line<<'\n';
      }
    from=file.tellg();
  }

  void ReadContent(ifstream &file, streampos &from, const string &findString)
  {
    string line;
    file.seekg(from);
    cout<<"readcontent"<<'\n';
    while(getline(file, line))
      {
	EraseLine(line);
	const unsigned size=line.size();
	// cout<<"line "<<line<<'\n';
	if(size==0) continue;
	else if(line.substr(0, 6)==findString or line==findString+"{")
	  {
	    cout<<"ReadContent "<<line<<" "<<size<<" "<<from<<'\n';
	    from=file.tellg();
	    // from+=size;
	    ReadInitialValues(file, from);
	    break;
	  }
      }
    from=file.tellg();
  }

  void ReadFile(const string &fileName, streampos &from)
  {
    string line;
    ifstream file(fileName);
    file.seekg(from);

    while(getline(file, line))
      {
	EraseLine(line);
	const unsigned size=line.size();

	if(size==0) continue;
	else if(line.substr(0, 6)=="vertex")
	  {
	    // from+=size;
	    // line=line.substr(7, size);
	    cout<<line<<" "<<from<<'\n';
	    ReadContent(file, from, "vertex");
	    // ReadContent(file, from, "values");
	    // ReadContent(file, from, "edges");
	    cout<<"----------"<<'\n';
	  }
	else if(line.substr(0, 5)=="edges")
	  {
	    // from+=size;
	    cout<<line<<" "<<from<<'\n';
	    ReadContent(file, from, "edges");
	    // line=line.substr(7, size);

	    cout<<"----------"<<'\n';
	  }
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
