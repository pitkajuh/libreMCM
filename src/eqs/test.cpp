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

vector<string> Remove(vector<string> equation, int open, int close)
{
  // cout<<"find "<<equation[open+1]<<" "<<equation[close+1]<<" size "<<equation.size()<<'\n';

  if(equation[open+1]==OPEN and equation[close+1]==CLOSE)
    {
      // cout<<"romenv "<<equation[open+1]<<" "<<equation[close+1]<<" "<<open+1<<" "<<close+1<<'\n';
      equation.erase(equation.begin()+open);
      equation.erase(equation.begin()+close-1);
      // open=distance(equation.begin(), find(equation.begin(), equation.end(), OPEN));
      // close=distance(equation.begin(), find(equation.begin(), equation.end(), CLOSE));

      // print_vector3(equation);

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
  // else
  //   {
  //     cout<<"ELSE"<<'\n';
  //     // open=distance(equation.begin(), find(equation.begin(), equation.end(), OPEN));
  //     // close=distance(equation.begin(), find(equation.begin(), equation.end(), CLOSE));
  //   }
  // print_vector3(equation);
  return equation;
}

bool IsOpen(vector<string> equation, const int open, const int close)
{
  const vector<string> tmp={equation.begin()+open+1, equation.begin()+close};
  // print_vector3(equation);
  // cout<<"tmp "<<open<<" "<<close<<'\n';
  // print_vector3(tmp);
  const int size=tmp.size();
  bool result=false;
  int open1=distance(tmp.begin(), find(tmp.begin(), tmp.end(), OPEN));
  if(open1==size) result=true;
  // cout<<"True or not "<<result<<'\n';
  return result;
}

vector<string> test33(vector<string> equation, int open, int close)
{
  // cout<<"test33 start"<<'\n';
  vector<string> tmp;
  int open2;
  int open3=open;
  bool end=false;
  // cout<<"oo "<<oo<<"open "<<open<<'\n';

  while(!end)
    {
      // cout<<"new round"<<'\n';
      tmp={equation.begin()+open+1, equation.begin()+close};
      // print_vector2(tmp);
      open2=distance(tmp.begin(), find(tmp.begin(), tmp.end(), OPEN));
      // cout<<"size open "<<open<<" open3 "<<open3<<" eqsize "<<equation.size()<<" tmpsize "<<tmp.size()<<" open2 "<<open2<<'\n';

      if(open2<tmp.size())
	{
	  // cout<<"open2<=tmp.size()"<<'\n';
	  open=distance(equation.begin()+open3+1, find(equation.begin()+open3+1, equation.end(), OPEN))+open3+1;
	  // cout<<"val open3 "<<open3<<" open "<<open<<" close "<<close<<" eq size"<<equation.size()<<'\n';
	  equation=GetParenthesis(equation, open, close);
	  open=distance(equation.begin(), find(equation.begin(), equation.end(), OPEN));
	  close=distance(equation.begin(), find(equation.begin(), equation.end(), CLOSE));
	  // cout<<"val new "<<" open "<<open<<" close "<<close<<" eq size"<<equation.size()<<'\n';
	  // print_vector2(equation);
	}
      else
	{
	  end=true;
	  // continue;
	}
    }
  // print_vector2(equation);
  // cout<<"test33 end"<<'\n';
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
      else equation=test33(equation, open, close);

    }
  return equation;
}
