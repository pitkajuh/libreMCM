#ifndef FILEGRAPH_H
#define FILEGRAPH_H

#include "File.h"

struct EdgeStruct
{
public:
  string from;
  string to;
  string equationName;
};

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
  void CreateEdges(const vector<string> &v);

public:
  // std::set<string> initialValueNames;
  vector<string> vertexNames;
  vector<EdgeStruct> edges;

  void InitResults(double *&results, const unsigned timeStart);
  FileGraph(const string &fileName, const unsigned timeStart, const unsigned timeEnd, const unsigned stepSize);

  FileGraph(){}
  ~FileGraph(){}
};

#endif
