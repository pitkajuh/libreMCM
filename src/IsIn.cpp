#include <vector>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

using std::map;
using std::string;
using std::vector;

const bool IsIn(const string &s, const map<string, string> &f)
{
  return f.find(s)!=f.end();
}

const bool IsIn(const string &s, const vector<string> &f)
{
  return std::find(f.begin(), f.end(), s)!=f.end();
}
