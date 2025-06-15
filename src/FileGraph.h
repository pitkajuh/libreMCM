#ifndef FILEGRAPH_H
#define FILEGRAPH_H

#include "File.h"
#include "GraphEquation.h"
#include <string_view>

using std::string_view;

struct EdgeStruct
{
public:
  string_view from;
  string_view to;
  string_view equationName;
};

class FileGraph: public File
{
protected:
  map<string, map<string, double>> all;

  string GetVertexName(string line);
  map<string, double> SetInitialValueName(vector<string> &ivs);
  streampos SA(ifstream &file, streampos from, const string &line);
  void CreateEdges(const vector<string> &v);
  void InitInitialValues(const string &vertex);
public:
  bool hasSink=0;
  bool hasSource=0;
  uint16_t nx=0;
  uint16_t ny=0;
  uint16_t N=0;
  vector<uint16_t> noOfInitialValue;
  std::set<string> vertexNames;
  map<string, uint16_t> vertexNamesMap;
  vector<EdgeStruct> edges;

  void CreateEdge(map<string, uint16_t> &equationNames, Equations &equations);
  void InitResults(double *&results);
  FileGraph(const string &fileName, const uint16_t timeStart, const uint16_t timeEnd, const uint16_t stepSize);

  FileGraph(){}
  ~FileGraph(){}
};

#endif
