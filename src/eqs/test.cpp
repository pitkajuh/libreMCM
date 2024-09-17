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

bool IsOpen(const vector<string> &tmp)
{
  bool result=false;
  const uint8_t open=distance(tmp.begin(), find(tmp.begin(), tmp.end(), OPEN));
  if(open==tmp.size()) result=true;
  return result;
}

vector<string> test2(vector<string> equation, uint8_t open, uint8_t close, uint8_t &id, const Data &data, Equation *&head, Equation *&next)
{
  bool end=false;
  vector<string> tmp;
  uint8_t open2;
  const uint8_t open3=open;

  while(!end)
    {
      tmp={equation.begin()+open+1, equation.begin()+close};
      open2=distance(tmp.begin(), find(tmp.begin(), tmp.end(), OPEN));

      if(open2<tmp.size())
	{
	  open=distance(equation.begin()+open3+1, find(equation.begin()+open3+1, equation.end(), OPEN))+open3+1;
	  equation=GetParenthesis(equation, open, close, id, data, head, next);
	  open=distance(equation.begin(), find(equation.begin(), equation.end(), OPEN));
	  close=distance(equation.begin(), find(equation.begin(), equation.end(), CLOSE));
	}
      else end=true;
    }
  return equation;
}

vector<string> test(vector<string> equation, uint8_t &id, const Data &data, Equation *&head, Equation *&next)
{
  bool end=false;
  bool is;
  uint8_t open;
  uint8_t close;
  vector<string> tmp;

  while(!end)
    {
      open=distance(equation.begin(), find(equation.begin(), equation.end(), OPEN));

      if(open>=equation.size()) break;

      close=distance(equation.begin(), find(equation.begin(), equation.end(), CLOSE));
      tmp={equation.begin()+open+1, equation.begin()+close};
      is=IsOpen(tmp);

      if(is) equation=GetParenthesis(equation, open, close, id, data, head, next);
      else equation=test2(equation, open, close, id, data, head, next);
    }
  return equation;
}
