#ifndef FILEEQUATIONS_H
#define FILEEQUATIONS_H

#include "FileGraph.h"
#include "GraphEquation.h"

class FileEquations: public File
{
protected:
  void print_vector2(const vector<string> &vec);
  vector<string> GetParenthesis(const vector<string> &equation, const uint8_t open, const uint8_t close, uint8_t &id, const vector<string> &data, GraphEquation *&graph);
  vector<string> RemoveOpenClose(vector<string> &equation);
  void Remove(vector<string> &equation, const uint8_t open, const uint8_t close);
  const bool IsOpen(const vector<string> &tmp);
  void test2(vector<string> &equation, uint8_t open, uint8_t close, uint8_t &id, const vector<string> &data, GraphEquation *&graph);
  void test(vector<string> &equation, uint8_t &id, const vector<string> &data, GraphEquation *&graph);
  void FindOperator(vector<string> &equation, const string &find, uint8_t &id, const vector<string> &data, GraphEquation *&graph);
  void ParseOperators(vector<string> &equation, uint8_t &id, const vector<string> &data, const uint8_t size, GraphEquation *&graph);
  void GetOrder(vector<string> &equation, uint8_t &id, const vector<string> &data, GraphEquation *&graph);
  void Convert(const map<string, string> &map);
  streampos SA(ifstream &file, streampos from, const string &line);
  string print_vector3(const vector<string> &vec);
  unsigned FindOperator(const string &eq, const unsigned size);
  vector<string> ToVector(string eq);
public:
  map<string, double> constants;
  map<string, string> equations;
  map<string, vector<string>> equations2;

  map<string, GraphEquation*> ParseEquations(const vector<string> &data);

  FileEquations(const string &fileName);

  FileEquations(){}
  ~FileEquations(){}
};

#endif
