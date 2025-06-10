#include <vector>
#include <algorithm>
#include <vector>
#include "namespace.h"

using namespace libremcm;
using std::vector;

const bool IsIn(const string &s, const SMap &f)
{
  return f.find(s)!=f.end();
}

const bool IsIn(const string &s, const std::vector<string> &f)
{
  return std::find(f.begin(), f.end(), s)!=f.end();
}
