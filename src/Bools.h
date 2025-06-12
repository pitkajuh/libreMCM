#ifndef BOOLS_H
#define BOOLS_H

#include <map>

using std::map;

struct Bools
{
public:
  bool variable=0;
  bool constant=0;
  bool numeric=0;
  bool math=0;
  bool negative=0;

  Bools(const string &s1, const map<string, uint16_t> &variables, const map<string, uint16_t> &constants)
  {
    variable=variables.find(s1)!=variables.end();
    negative=s1[0]=='-';
    constant=(negative)?constants.find(s1.substr(1))!=constants.end():constants.find(s1)!=constants.end();
    math=(s1.substr(0, 1)=="@")?1:0;

    if(!variable and !constant and !math) numeric=1;
  }
};

#endif
