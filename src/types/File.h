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
  const string vertex="vertex";
  const string edges="edges";

  void EraseLine(string &line)
  {
    line.erase(remove(line.begin(), line.end(), ' '), line.end());
  }

  streampos ReadInitialValues(ifstream &file, streampos from)
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
    return file.tellg();
  }

  streampos ReadContent(ifstream &file, streampos from, const string &findString)
  {
    string line;
    file.seekg(from);

    while(getline(file, line))
      {
	EraseLine(line);
	const unsigned size=line.size();

	if(size==0) continue;
	else if(line.substr(0, 6)==findString or line==findString+"{")
	  {
	    cout<<"ReadContent "<<line<<'\n';
	    from=file.tellg();
	    from=ReadInitialValues(file, from);
	    break;
	  }
      }
    return file.tellg();
  }

  void ReadFile(const string &fileName)
  {
    streampos from=0;
    string line;
    ifstream file(fileName);
    file.seekg(from);

    while(getline(file, line))
      {
	EraseLine(line);
	const unsigned size=line.size();

	if(size==0) continue;
	else if(line.substr(0, 6)==vertex)
	  {
	    from=ReadContent(file, from, vertex);
	  }
	else if(line.substr(0, 5)==edges)
	  {
	    from=ReadContent(file, from, edges);
	  }
	cout<<"----------"<<'\n';
      }
  }
public:
  File(){}
  virtual ~File(){}
};

class FileGraph: public File
{
public:
  FileGraph(const string &fileName)
  {
    ReadFile(fileName);
  }

  FileGraph(){}
  ~FileGraph(){}
};

#endif
