/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../global/mathconst.h"
#include "ToVector.h"
#include "ParseEquations.h"
#include <unordered_map>
#include <algorithm>
#include <iostream>

using std::unordered_map;
using std::to_string;
using std::cout;

vector<string> Remove(vector<string> equation, const int open, const int close)
{
  if(equation[open+1]==OPEN and equation[close+1]==CLOSE)
    {
      equation.erase(equation.begin()+open);
      equation.erase(equation.begin()+close-1);
      equation=RemoveOpenClose(equation);
    }
  return equation;
}

bool IsOpen(vector<string> equation, const int open, const int close, const vector<string> tmp)
{
  const int size=tmp.size();
  bool result=false;
  int open1=distance(tmp.begin(), find(tmp.begin(), tmp.end(), OPEN));
  if(open1==size) result=true;
  return result;
}

vector<string> test2(vector<string> equation, int open, int close)
{
  vector<string> tmp;
  int open2;
  const int open3=open;
  bool end=false;

  while(!end)
    {
      tmp={equation.begin()+open+1, equation.begin()+close};
      open2=distance(tmp.begin(), find(tmp.begin(), tmp.end(), OPEN));

      if(open2<tmp.size())
	{
	  open=distance(equation.begin()+open3+1, find(equation.begin()+open3+1, equation.end(), OPEN))+open3+1;
	  equation=GetParenthesis(equation, open, close);
	  open=distance(equation.begin(), find(equation.begin(), equation.end(), OPEN));
	  close=distance(equation.begin(), find(equation.begin(), equation.end(), CLOSE));
	}
      else end=true;
    }
  return equation;
}

vector<string> test(vector<string> equation)
{
  bool end=false;
  bool is;
  int open;
  int close;
  vector<string> tmp;

  while(!end)
    {
      open=distance(equation.begin(), find(equation.begin(), equation.end(), OPEN));

      if(open>=equation.size()) break;

      close=distance(equation.begin(), find(equation.begin(), equation.end(), CLOSE));
      tmp={equation.begin()+open+1, equation.begin()+close};
      is=IsOpen(equation, open, close, tmp);

      if(is) equation=GetParenthesis(equation, open, close);
      else equation=test2(equation, open, close);
    }
  return equation;
}
