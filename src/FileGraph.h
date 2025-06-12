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
  map<string, double> SetInitialValueName(vector<string> &ivs);
  streampos SA(ifstream &file, streampos from, const string &line);
  void CreateEdges(const vector<string> &v);
  void InitInitialValues(const string &vertex);
public:
  uint16_t nx=0;
  uint16_t ny=0;
  uint16_t N=0;
  vector<uint16_t> noOfInitialValue;
  vector<string> vertexNames;
  map<string, uint16_t> vertexNamesMap;
  vector<EdgeStruct> edges;

  void InitResults(double *&results);
  FileGraph(const string &fileName, const uint16_t timeStart, const uint16_t timeEnd, const uint16_t stepSize);

  FileGraph(){}
  ~FileGraph(){}
};

#endif
