#ifndef BOOLS_H
#define BOOLS_H

#include <map>

using std::map;

struct Bools
{
private:
  const bool IsIn(const string &s, const map<string, string> &f)
  {
    return f.find(s)!=f.end();
  }

  const bool IsIn(const string &s, const vector<string> &f)
  {
    return std::find(f.begin(), f.end(), s)!=f.end();
  }
public:
  bool variable=0;
  bool constant=0;
  bool numeric=0;
  bool math=0;
  bool negative=0;

  Bools(const string &s1, const vector<string> &variables, const map<string, uint16_t> &constants)
  {
    variable=IsIn(s1, variables);
    negative=s1[0]=='-';
    constant=(negative)?constants.find(s1.substr(1))!=constants.end():constants.find(s1)!=constants.end();
    math=(s1.substr(0, 1)=="@")?1:0;

    if(!variable and !constant and !math) numeric=1;
  }
};

#endif
