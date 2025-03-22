/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../types/MathOperation.h"
#include "../global/mathconst.h"
#include "ToVector.h"
#include "ParseEquations.h"
#include <algorithm>
#include <iostream>
#include "../types/Graph.h"

using std::to_string;
using std::cout;

vector<string> Remove(vector<string> equation, const uint8_t open, const uint8_t close)
{
  if(equation[open+1]==OPEN and equation[close+1]==CLOSE)
    {
      equation.erase(equation.begin()+open);
      equation.erase(equation.begin()+close-1);
      equation=RemoveOpenClose(equation);
    }
  return equation;
}

const bool IsOpen(const vector<string> &tmp)
{
  const uint8_t op=distance(tmp.begin(), find(tmp.begin(), tmp.end(), OPEN));

  if(op==tmp.size()) return 1;
  return 0;
}

vector<string> test2(vector<string> equation, uint8_t open, uint8_t close, uint8_t &id, const vector<string> &data, Equation *&head, Equation *&next, GraphEquation *&graph)
{
  const vector<string> tmp={equation.begin()+open+1, equation.begin()+close};
  const uint8_t op=distance(tmp.begin(), find(tmp.begin(), tmp.end(), OPEN));

  if(op<tmp.size())
    {
      open=distance(equation.begin()+open+1, find(equation.begin()+open+1, equation.end(), OPEN))+open+1;
      equation=GetParenthesis(equation, open, close, id, data, head, next, graph);
      open=distance(equation.begin(), find(equation.begin(), equation.end(), OPEN));
      close=distance(equation.begin(), find(equation.begin(), equation.end(), CLOSE));
      equation=test2(equation, open, close, id, data, head, next, graph);
    }
  return equation;
}

vector<string> test(vector<string> equation, uint8_t &id, const vector<string> &data, Equation *&head, Equation *&next, GraphEquation *&graph)
{
  uint8_t open=distance(equation.begin(), find(equation.begin(), equation.end(), OPEN));
  uint8_t close;
  vector<string> tmp;

  while(open<equation.size())
    {
      close=distance(equation.begin(), find(equation.begin(), equation.end(), CLOSE));
      tmp={equation.begin()+open+1, equation.begin()+close};

      if(IsOpen(tmp)) equation=GetParenthesis(equation, open, close, id, data, head, next, graph);
      else equation=test2(equation, open, close, id, data, head, next, graph);
      open=distance(equation.begin(), find(equation.begin(), equation.end(), OPEN));
    }
  return equation;
}
