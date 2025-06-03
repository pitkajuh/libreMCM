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
#include <vector>
#include <utility>
#include <set>
#include <map>

using std::map;
using std::cout;
using std::vector;
using std::pair;

class File
{
protected:
  void EraseLine(string &line)
  {
    line.erase(remove(line.begin(), line.end(), ' '), line.end());
  }

  pair<streampos, vector<string>> ReadContentSub(ifstream &file, streampos from)
  {
    string line;
    vector<string> content;
    file.seekg(from);

    while(getline(file, line))
      {
	EraseLine(line);
	if(line.size()==0 or line=="{") continue;
	else if(line=="}") break;
	else
	  {
	    cout<<line<<'\n';
	    content.emplace_back(line);
	  }
      }
    return {file.tellg(), content};
  }

  pair<streampos, vector<string>> ReadContent(ifstream &file, streampos from, const string &findString, const unsigned size)
  {
    string line;
    pair<streampos, vector<string>> result;
    file.seekg(from);

    while(getline(file, line))
      {
	EraseLine(line);

	if(line.size()==0) continue;
	else if(line.substr(0, size)==findString or line==findString+"{")
	  {
	    result=ReadContentSub(file, file.tellg());
	    break;
	  }
      }
    return result;
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

	if(line.size()==0) continue;
	SA(file, from, line);
      }

    file.close();
  }

public:
  virtual void SA(ifstream &file, streampos &from, const string &line)=0;
  File(){}
  virtual ~File(){}
};

class FileEquations: public File
{
protected:
  void SA(ifstream &file, streampos &from, const string &line)
  {
    pair<streampos, vector<string>> result;
    string vertexName;
    const string vertex="constants";
    const string edges="equations";

    if(line.substr(0, vertex.size())==vertex)
      {
	// vertexName=GetVertexName(line);
	result=ReadContent(file, from, vertex, vertex.size());
	// from=result.first;
	// all[vertexName]=SetInitialValueName(result.second);
      }
    else if(line.substr(0, edges.size())==edges)
      {
	result=ReadContent(file, from, edges, edges.size());
	// from=result.first;
      }
  }
public:

  FileEquations(const string &fileName)
  {
    ReadFile(fileName);
  }

  FileEquations(){}
  ~FileEquations(){}
};

class FileSettings: public File
{
protected:
  map<string, string> GetSettings(const vector<string> &ivs)
  {
    string name;
    string value;
    map<string, string> result;

    for(const auto &iv: ivs)
      {
	const unsigned at=iv.find("=");
	name=iv.substr(0, at);
	value=iv.substr(at+1, iv.size()-1);
	result[name]=value;
      }
    return result;
  }

  void SA(ifstream &file, streampos &from, const string &line)
  {
    pair<streampos, vector<string>> result;
    const string settings="simulation_settings";
    const unsigned size=settings.size();

    if(line.substr(0, size)==settings)
      {
	result=ReadContent(file, from, settings, size);
	set=GetSettings(result.second);
      }
  }
public:
  map<string, string> set;

  FileSettings(const string &fileName)
  {
    ReadFile(fileName);
  }

  FileSettings(){}
  ~FileSettings(){}
};

class FileGraph: public File
{
protected:
  string GetVertexName(string line)
  {
    line.erase(line.begin(), line.begin()+6);

    if(line.back()=='{') line.erase(line.end()-1);

    return line;
  }

  std::set<string> initialValueNames;
  map<string, map<string, double>> all;
  unsigned nx=0;
  unsigned ny=0;
  unsigned n=0;
  unsigned N=0;

  map<string, double> SetInitialValueName(const vector<string> &ivs)
  {
    string name;
    double value;
    map<string, double> result;

    for(const auto &iv: ivs)
      {
	const unsigned at=iv.find("=");
	name=iv.substr(0, at);
	value=std::stod(iv.substr(at+1, iv.size()-1));
	initialValueNames.insert(name);
	result[name]=value;
      }
    return result;
  }

  void SA(ifstream &file, streampos &from, const string &line)
  {
    pair<streampos, vector<string>> result;
    string vertexName;
    const string vertex="vertex";
    const string edges="edges";

    if(line.substr(0, 6)==vertex)
      {
	vertexName=GetVertexName(line);
	result=ReadContent(file, from, vertex, 6);
	from=result.first;
	all[vertexName]=SetInitialValueName(result.second);
      }
    else if(line.substr(0, 5)==edges)
      {
	result=ReadContent(file, from, edges, 5);
	from=result.first;
      }
  }

public:
  void InitResults(double *&results, const unsigned timeStart)
  {
    N=1+n*(1+nx*ny);
    results=new double[N];
    results[0]=timeStart;

    unsigned i=1;

    for(auto &[name, value]: all)
      {
	for(const auto&[v1, v2]: value)
	  {
	    results[i]=v2;
	    i++;
	  }
      }

    all.clear();

    for(unsigned i=0; i<n*nx; i++)
      {
	cout<<"i="<<i<<" "<<results[i]<<'\n';
      }
  }

  FileGraph(const string &fileName, const unsigned timeStart, const unsigned timeEnd, const unsigned stepSize)
  {
    ny=(timeEnd-timeStart)/stepSize;
    ReadFile(fileName);


    for(auto &[name, value]: all)
      {
	for(const string &v: initialValueNames)
	  {
	    value[v];
	  }
      }

    nx=initialValueNames.size();
    n=all.size();
  }

  FileGraph(){}
  ~FileGraph(){}
};

#endif
