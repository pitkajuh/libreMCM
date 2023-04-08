/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef EQUATIONS_H
#define EQUATIONS_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Equations
{
 public:
  vector<vector<string>> equations;

  void push_back(const vector<string> equation)
  {
    equations.push_back(equation);
  }
  void clear()
  {
    equations.clear();
  }
  int size()
  {
    int size=equations.size();
    return size;
  }
  vector<string>& operator[](const int i)
  {
    return equations[i];
  }
  const vector<string>& operator[](const int i) const
  {
    return equations[i];
  }
};

#endif
