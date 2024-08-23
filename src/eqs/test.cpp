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

vector<string> Remove(vector<string> equation, const int &open, const int &close)
{
  if(equation[open+1]==OPEN and equation[close+1]==CLOSE)
  // if(equation[open]==OPEN and equation[close]==CLOSE)
    {
      equation.erase(equation.begin()+open);
      equation.erase(equation.begin()+close-1);
      equation=RemoveOpenClose(equation);
    }
  return equation;
}

bool IsOpen(const unsigned int &open, const unsigned int &close, const vector<string> &tmp)
{
  bool result=false;
  unsigned int open1=distance(tmp.begin(), find(tmp.begin(), tmp.end(), OPEN));
  if(open1==tmp.size()) result=true;
  return result;
}

vector<string> test2(vector<string> equation, unsigned int &open, unsigned int &close, unsigned int &k, const Data &data, Equation *e, Equation *next, EquationStruct &eq)
{
  bool end=false;
  vector<string> tmp;
  unsigned int open2;
  const unsigned int open3=open;

  while(!end)
    {
      tmp={equation.begin()+open+1, equation.begin()+close};
      open2=distance(tmp.begin(), find(tmp.begin(), tmp.end(), OPEN));

      if(open2<tmp.size())
	{
	  open=distance(equation.begin()+open3+1, find(equation.begin()+open3+1, equation.end(), OPEN))+open3+1;
	  equation=GetParenthesis(equation, open, close, k, data, e, next, eq);
	  open=distance(equation.begin(), find(equation.begin(), equation.end(), OPEN));
	  close=distance(equation.begin(), find(equation.begin(), equation.end(), CLOSE));
	}
      else end=true;
    }
  return equation;
}

vector<string> test(vector<string> equation, unsigned int &k, const Data &data, Equation *&e, Equation *&next, EquationStruct &eq)
{
  bool end=false;
  bool is;
  unsigned int open;
  unsigned int close;
  vector<string> tmp;

  while(!end)
    {
      open=distance(equation.begin(), find(equation.begin(), equation.end(), OPEN));

      if(open>=equation.size()) break;

      close=distance(equation.begin(), find(equation.begin(), equation.end(), CLOSE));
      tmp={equation.begin()+open+1, equation.begin()+close};
      is=IsOpen(open, close, tmp);

      if(is) equation=GetParenthesis(equation, open, close, k, data, e, next, eq);
      else equation=test2(equation, open, close, k, data, e, next, eq);
    }
  return equation;
}
