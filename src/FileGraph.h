/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef FILEGRAPH_H
#define FILEGRAPH_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <map>
#include "File.h"

using std::map;
using std::cout;
using std::vector;
using std::pair;
using std::streampos;
using std::ifstream;

class FileGraph: public File
{
protected:
  string GetVertexName(string line);

  map<string, map<string, double>> all;

  unsigned nx=0;
  unsigned ny=0;
  unsigned n=0;
  unsigned N=0;

  map<string, double> SetInitialValueName(const vector<string> &ivs);
  streampos SA(ifstream &file, streampos from, const string &line);

public:
  std::set<string> initialValueNames;
  vector<string> vertexNames;

  void InitResults(double *&results, const unsigned timeStart);
  FileGraph(const string &fileName, const unsigned timeStart, const unsigned timeEnd, const unsigned stepSize);

  FileGraph(){}
  ~FileGraph(){}
};

#endif
