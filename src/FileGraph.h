#ifndef FILEGRAPH_H
#define FILEGRAPH_H

#include "File.h"
#include "Edge.h"
#include "Equation.h"

using std::set;

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
  map<string, map<string, double>> all;
  map<string, map<string, double>> sinkMap;

  string GetVertexName(string line);
  map<string, double> SetInitialValueName(vector<string> &ivs);
  streampos SA(ifstream &file, streampos from, const string &line);
  void CreateEdges(const vector<string> &v);
  void InitInitialValues();
public:
  bool hasSink=0;
  bool hasSource=0;
  uint16_t nx=0;
  uint16_t ny=0;
  uint16_t N=0;
  vector<uint16_t> noOfInitialValue;
  vector<uint16_t> noivs;
  set<string> vertexNames;
  map<string, uint16_t> vertexNamesMap;
  map<string, std::pair<set<string>, set<string>>> vertexEquationsAddSubtract;
  vector<EdgeStruct> edges;
  vector<Edge> edgesNew;
  vector<Edge2> edgesNew2;

  void CreateEdge(map<string, uint16_t> &equationNames, Equations &equations, const vector<uint16_t> &noivs, const vector<uint16_t> &noOfInitialValue);
  void InitResults(double *&results);
  FileGraph(const string &fileName, const uint16_t timeStart, const uint16_t timeEnd, const uint16_t stepSize);

  FileGraph(){}
  ~FileGraph(){}
};

#endif
