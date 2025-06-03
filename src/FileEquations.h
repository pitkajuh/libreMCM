#ifndef FILEEQUATIONS_H
#define FILEEQUATIONS_H

#include "File.h"

class FileEquations: public File
{
protected:
  void Convert(const map<string, string> &map);
  streampos SA(ifstream &file, streampos from, const string &line);
  string print_vector3(const vector<string> &vec);
  unsigned FindOperator(const string &eq, const unsigned size);
  vector<string> ToVector(string eq);
public:
  map<string, double> constants;
  map<string, string> equations;
  map<string, vector<string>> equations2;

  FileEquations(const string &fileName);

  FileEquations(){}
  ~FileEquations(){}
};

#endif
