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
  void ReadContent(ifstream &file, streampos &from)
  {
    string line;
    string linePrevious;
    file.seekg(from);

    while(getline(file, line) and line!="}")
      {
	line.erase(remove(line.begin(), line.end(), ' '), line.end());
	// line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
	cout<<"ReadContent "<<line<<" "<<line.size()<<'\n';

	linePrevious=line;
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
	// cout<<line<<" "<<line.size()<<'\n';
	if(line=="{")
	  {
	    // cout<<"line=={"<<'\n';
	    // from+=1;
	    // file.seekg(from);
	    cout<<"Reading "<<linePrevious<<'\n';
	    ReadContent(file, from);
	    cout<<" "<<'\n';
	    // Read content
	  }
	linePrevious=line;
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
