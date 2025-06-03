/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef FILEEQUATIONS_H
#define FILEEQUATIONS_H

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
