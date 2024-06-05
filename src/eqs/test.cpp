/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "ToVector.h"
#include "ParseEquations.h"
#include <unordered_map>
#include <algorithm>
#include <iostream>

using std::unordered_map;
using std::to_string;
using std::cout;

const string OPEN="(";
const string CLOSE=")";

void print_vector3(vector<string> vec)
{
  int i=0;
  string empty="";

  if(vec.size()>0)
    {
      while(i<=vec.size()-1)
	{
	  if(i==0)
	    {
	      empty=vec[i];
	    }
	  else
	    {
	      empty=empty+";"+vec[i];
	    }
	  i++;
	}
      cout<<empty<<'\n';
    }
}

bool IsOpen(vector<string> equation, const int open, const int close)
{
  const vector<string> tmp={equation.begin()+open+1, equation.begin()+close};
  cout<<"tmp"<<'\n';
  print_vector3(tmp);
  const int size=tmp.size();
  bool result=false;
  int open1=distance(tmp.begin(), find(tmp.begin(), tmp.end(), OPEN));
  if(open1==size) result=true;
  return result;
}

vector<string> Remove(vector<string> equation, int open, int close)
{
  cout<<"find "<<equation[open+1]<<" "<<equation[close+1]<<" size "<<equation.size()<<'\n';

  if(equation[open+1]==OPEN and equation[close+1]==CLOSE)
    {
      cout<<"romenv "<<equation[open+1]<<" "<<equation[close+1]<<" "<<open+1<<" "<<close+1<<'\n';
      equation.erase(equation.begin()+open);
      // equation.erase(equation.begin()+open+1);
      // equation.erase(equation.begin()+close-1);
      equation.erase(equation.begin()+close-1);
      // open=distance(equation.begin(), find(equation.begin(), equation.end(), OPEN));
      // close=distance(equation.begin(), find(equation.begin(), equation.end(), CLOSE));
      print_vector3(equation);
      // cout<<"size now "<<equation.size()<<" "<<open<<" "<<close<<'\n';
      // bool is=IsOpen(equation, open, close);
      // cout<<is<<'\n';
      // if(is) equation=RemoveOpenClose(equation);
      equation=RemoveOpenClose(equation);
      // else
      // 	{
      // 	  equation.erase(equation.begin()+open);
      // 	  equation.erase(equation.begin()+close);
      // 	}
    }
  else
    {
      cout<<"ELSE"<<'\n';
    }
  print_vector3(equation);
  return equation;
}

vector<string> test(vector<string> equation)
{
  bool end=false;
  bool is;
  int open;
  int close;

  while(!end)
    {
      open=distance(equation.begin(), find(equation.begin(), equation.end(), OPEN));

      if(open>=equation.size()) break;

      close=distance(equation.begin(), find(equation.begin(), equation.end(), CLOSE));
      is=IsOpen(equation, open, close);

      if(is) equation=GetParenthesis(equation, open, close);
      else
	{
	  end=true;
	  continue;
	}
    }
  return equation;
}
