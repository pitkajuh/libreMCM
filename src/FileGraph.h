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

  uint16_t nx=0;
  uint16_t ny=0;
  uint16_t n=0;
  uint16_t N=0;

  map<string, double> SetInitialValueName(const vector<string> &ivs);
  streampos SA(ifstream &file, streampos from, const string &line);
  void CreateEdges(const vector<string> &v);

public:
  // std::set<string> initialValueNames;
  vector<string> vertexNames;
  vector<EdgeStruct> edges;

  void InitResults(double *&results, const uint16_t timeStart);
  FileGraph(const string &fileName, const uint16_t timeStart, const uint16_t timeEnd, const uint16_t stepSize);

  FileGraph(){}
  ~FileGraph(){}
};

#endif
