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

  void push_back(vector<string> equation)
  {
    equations.push_back(equation);
  }
  void clear()
  {
    equations.clear();
  }
  int get_size()
  {
    int size=equations.size();
    return size;
  }
  vector<string> get(int i)
  {
    vector<string> result=equations[i];
    return result;
  }
  void replace(vector<string> equation, int i)
  {
    equations[i]=equation;
  }
};

#endif
