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
	from=SA(file, from, line);
      }

    file.close();
  }

public:
  virtual streampos SA(ifstream &file, streampos from, const string &line)=0;
  File(){}
  virtual ~File(){}
};

class FileEquations: public File
{
protected:
  void Convert(const map<string, string> &map)
  {
    for(const auto &[key, value]: map)
      {
	constants[key]=std::stod(value);
      }
  }

  streampos SA(ifstream &file, streampos from, const string &line)
  {
    pair<streampos, vector<string>> result;
    const string constants1="constants";
    const string equations1="equations";
    const string sub=line.substr(0, 9);

    if(sub==constants1)
      {
	result=ReadContent(file, from, constants1, 9);
	Convert(GetSettings(result.second));
      }
    else if(sub==equations1)
      {
	result=ReadContent(file, from, equations1, 9);
	equations=GetSettings(result.second);
      }
    from=result.first;
    return from;
  }
  void ToVector(string eq)
  {
    vector<string> equation;
    const string DIVIDE="/";
    const string MULTIPLY="*";
    const string ADD="+";
    const string SUBTRACT="-";
    const string OPEN="(";
    const string CLOSE=")";
    const string EXP="^";
    const array<string, 7> OPERATORS2={EXP, DIVIDE, MULTIPLY, ADD, SUBTRACT, OPEN, CLOSE};
    unsigned size=eq.size();

    while(size>0)
      {
	unsigned smallest=size;

	for(const auto &i: OPERATORS2)
	  {
	    const unsigned a=eq.find(i);

	    if(a<size and a<smallest) smallest=a;

	  }
	// Check edge cases here
	// e.g. if smallest=0 and eq[smallest]=/, then it is illegal operation
	// smallest=0 eq[smallest]=- is ok
	cout<<smallest<<" "<<eq[smallest]<<'\n';

	break;
      }
  }
public:
  map<string, double> constants;
  map<string, string> equations;

  FileEquations(const string &fileName)
  {
    ReadFile(fileName);
    for(const auto &[i, v]: constants)
      {
	cout<<i<<" "<<v<<'\n';
      }
    cout<<" "<<'\n';
    for(const auto &[i, v]: equations)
      {
	cout<<i<<" "<<v<<'\n';
	ToVector(v);
      }
  }

  FileEquations(){}
  ~FileEquations(){}
};

class FileSettings: public File
{
protected:
  streampos SA(ifstream &file, streampos from, const string &line)
  {
    pair<streampos, vector<string>> result;
    const string settings="simulation_settings";

    if(line.substr(0, 19)==settings)
      {
	result=ReadContent(file, from, settings, 19);
	set=GetSettings(result.second);
      }
    from=result.first;
    return from;
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

  streampos SA(ifstream &file, streampos from, const string &line)
  {
    pair<streampos, vector<string>> result;
    string vertexName;
    const string vertex="vertex";
    const string edges="edges";

    if(line.substr(0, 6)==vertex)
      {
	vertexName=GetVertexName(line);
	result=ReadContent(file, from, vertex, 6);
	all[vertexName]=SetInitialValueName(result.second);
      }
    else if(line.substr(0, 5)==edges)
      {
	result=ReadContent(file, from, edges, 5);
      }
    from=result.first;
    return from;
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
