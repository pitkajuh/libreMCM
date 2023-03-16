/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef SOLUTIONS_H
#define SOLUTIONS_H

#include "Solution.h"

class Solutions
{
 public:
  vector<vector<Solution>> solutions;

  void push_back(const vector<Solution> solution)
  {
    solutions.push_back(solution);
  }
  void clear()
  {
    solutions.clear();
  }
  int size()
  {
    int size=solutions.size();
    return size;
  }
  vector<Solution>& operator[](const int i)
  {
    return solutions[i];
  }
  const vector<Solution>& operator[](const int i) const
  {
    return solutions[i];
  }
};

#endif
