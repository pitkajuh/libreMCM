#ifndef FILEGRAPH_H
#define FILEGRAPH_H

#include "File.h"
#include "Edge.h"
#include "Equation.h"
#include "Vertex.h"
#include "FileSettings.h"
#include "Graph.h"

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
  string GetVertexName(string line);
  map<string, double> SetInitialValueName(vector<string> &ivs);
  streampos SA(ifstream &file, streampos from, const string &line);
  void CreateEdges(const vector<string> &v);
public:
  map<string, map<string, double>> vertexInitialValueMap;
  uint16_t nx=0;
  uint16_t ny=0;
  uint16_t N=0;
  vector<uint16_t> noOfInitialValue;

  set<string> vertexNames;
  map<string, uint16_t> vertexNamesMap;

  map<string, std::pair<set<string>, set<string>>> vertexEquationsAddSubtract;
  vector<EdgeStruct> edges;
  void InitInitialValues();
  void CreateGraph(const FileSettings &simulationParameters);
  void CreateEdge(Graph &graph, map<string, uint16_t> &equationNames, Equations &equations);
  void CreateVertices(Graph &graph, vector<double> &results);
  FileGraph(const string &fileName, const FileSettings &simulationParameters);
  void Read(const string &fileName);
  void Create(const FileSettings &simulationParameters);

  FileGraph(){}
  ~FileGraph(){}
};

#endif
