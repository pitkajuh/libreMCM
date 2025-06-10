#ifndef ISIN_H
#define ISIN_H

#include <vector>
#include "namespace.h"

using namespace libremcm;
using std::vector;

const bool IsIn(const string &s, const SMap &f);
const bool IsIn(const string &s, const vector<string> &f);

#endif
