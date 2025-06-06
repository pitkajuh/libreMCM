#ifndef FILEEQUATIONS_H
#define FILEEQUATIONS_H

#include "FileGraph.h"
#include "GraphEquation.h"

class FileEquations: public File
{
protected:
  void print_vector2(const vector<string> &vec);
  vector<string> GetParenthesis(const vector<string> &equation, const uint8_t open, const uint8_t close, uint8_t &id, const vector<string> &data, GraphEquation *&graph);
  void RemoveOpenClose(vector<string> &equation);
  void Remove(vector<string> &equation, const uint8_t open, const uint8_t close);
  uint8_t test2(vector<string> &equation, uint8_t open, uint8_t close, uint8_t id, const vector<string> &data, GraphEquation *&graph);
  uint8_t test(vector<string> &equation, uint8_t id, const vector<string> &data, GraphEquation *&graph);
  uint8_t FindOperator(vector<string> &equation, const string &find, uint8_t id, const vector<string> &data, GraphEquation *&graph);
  uint8_t ParseOperators(vector<string> &equation, uint8_t id, const vector<string> &data, const uint8_t size, GraphEquation *&graph);
  void GetOrder(vector<string> &equation, uint8_t id, const vector<string> &data, GraphEquation *&graph);
  void Convert(const map<uint16_t, string> &map);
  streampos SA(ifstream &file, streampos from, const string &line);
  string print_vector3(const vector<string> &vec);
  uint8_t FindOperator(const string &eq, const uint8_t size);
  vector<string> ToVector(string eq);
public:
  map<uint16_t, double> constants;
  map<uint16_t, string> equations;
  map<string, uint16_t> equationNames;
  map<string, uint16_t> constantNames;

  map<uint16_t, GraphEquation*> ParseEquations(const vector<string> &data);

  FileEquations(const string &fileName);

  FileEquations(){}
  ~FileEquations(){}
};

#endif
