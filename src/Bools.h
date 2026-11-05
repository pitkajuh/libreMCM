#ifndef BOOLS_H
#define BOOLS_H

#include <cstdint>
#include <string>
#include <map>
#include "Graph.h"

using std::map;
using std::string;

struct Bools
{
public:
  bool variable=0;
  bool constant=0;
  bool numeric=0;
  bool math=0;
  bool negative=0;

  Bools(const string &s1, Graph &graph, const map<string, uint16_t> &constants)
  {
    variable=graph.FindVertex(s1);
    negative=s1[0]=='-';
    constant=(negative)?constants.find(s1.substr(1))!=constants.end():constants.find(s1)!=constants.end();
    math=(s1.substr(0, 1)=="@")?1:0;

    if(!variable and !constant and !math) numeric=1;
  }
};

#endif
