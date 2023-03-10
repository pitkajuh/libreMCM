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

  void push_back(vector<Solution> solution)
  {
    solutions.push_back(solution);
  }
  void clear()
  {
    solutions.clear();
  }
  int get_size()
  {
    int size=solutions.size();
    return size;
  }
  vector<Solution> get(int i)
  {
    vector<Solution> result=solutions[i];
    return result;
  }
  void replace(vector<Solution> solution, int i)
  {
    solutions[i]=solution;
  }
};

#endif
