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
#include <unordered_map>
#include <algorithm>
#include <iostream>

using std::unordered_map;
using std::to_string;
using std::cout;

vector<string> GetEquation(const vector<string> equation, const int open, const int close)
{
  vector<string> r;
  const vector<string> tmp2={equation.begin(), equation.begin()+open};
  const vector<string> tmp={equation.begin()+open+1, equation.begin()+close};
  const vector<string> tmp3={equation.begin()+close+1, equation.end()};
  r.insert(r.begin(), tmp2.begin(), tmp2.end());
  r.insert(r.end(), tmp.begin(), tmp.end());
  r.insert(r.end(), tmp3.begin(), tmp3.end());
  return r;
}

bool IsOpen(vector<string> equation, int open, const int close)
{
  bool result=false;
  vector<string> tmp={equation.begin()+open+1, equation.begin()+close};
  open=distance(tmp.begin(), find(tmp.begin(), tmp.end(), "("));
  if(open==tmp.size()) result=true;
  return result;
}

vector<string> FindOperator(vector<string> equation, const string find)
{
  int i=0;
  static int k=0;
  // MathOperation op;

  while(i<equation.size())
     {
       if(find==equation[i])
	 {
	   // op.SetValue1(equation[i-1]);
	   // op.SetValue2(equation[i+1]);
	   // op.SetMathOp(equation[i]);
	   // op.id="T"+to_string(k);

	   // MathOperation op(equation[i-1], equation[i], equation[i+1]);
	   // Do something with op;

	   cout<<"T"+to_string(k)<<"="<<equation[i-1]<<equation[i]<<equation[i+1]<<'\n';
	   equation[i]="T"+to_string(k);
	   // equation_map1["T"+to_string(k)]=op;
	   equation.erase(equation.begin()+i+1);
	   equation.erase(equation.begin()+i-1);
	   k++;
	   i=0;
	   continue;
	 }
       i++;
     }
  // delete op;
  // op.~MathOperation();
  return equation;
}

vector<string> GetOrder(vector<string> equation)
{
  const vector<string> operators={"/", "*", "+", "-"};
  for(const auto&i: operators) equation=FindOperator(equation, i);
  return equation;
}

vector<string> test33(vector<string> equation, int open, int close)
{
  vector<string> tmp;
  int open4;
  int open3=open;
  bool end=false;

  while(end==false)
    {
      tmp={equation.begin()+open+1, equation.begin()+close};
      open4=distance(tmp.begin(), find(tmp.begin(), tmp.end(), "("));

      if(open4<tmp.size())
	{
	  open=distance(equation.begin()+open3+1, find(equation.begin()+open3+1, equation.end(), "("))+open3+1;
	  equation=GetEquation(equation, open, close);
	  open=distance(equation.begin(), find(equation.begin(), equation.end(), "("));
	  close=distance(equation.begin(), find(equation.begin(), equation.end(), ")"));
	}
      else
	{
	  end=true;
	  continue;
	}
    }
  // print_vector2(equation);
  // cout<<"test33 end"<<'\n';
  return equation;
}

vector<string> test3(vector<string> equation)
{
  bool end=false;
  bool is=false;
  int close;
  int open;
  // equation=RemoveOpenClose(equation);

  // cout<<"test3"<<'\n';
  while(end==false)
    {
      // cout<<"test3 "<<close<<" "<<open<<'\n';
      // print_vector2(equation);
      close=distance(equation.begin(), find(equation.begin(), equation.end(), ")"));
      open=distance(equation.begin(), find(equation.begin(), equation.end(), "("));

      if(open>=equation.size()) break;

      is=IsOpen(equation, open, close);

      if(is)
	{
	  // cout<<is<<'\n';
	  equation=GetEquation(equation, open, close);
	  continue;
	}
      else
	{
	  // cout<<"ELSE"<<'\n';
	  // print_vector2(equation);
	  equation=test33(equation, open, close);
	  // cout<<"test3"<<'\n';
	  // print_vector2(equation);
	}
    }
  // cout<<"test3 loop end"<<'\n';
  equation=GetOrder(equation);
  // cout<<"RESULT"<<'\n';
  // print_vector2(equation);
  return equation;
}

void ParseEquations(const unordered_map<string, string> equations_map)
{
  string name;
  string equation;
  vector<string> v;

  for(auto i=equations_map.begin(); i!=equations_map.end(); i++)
    {
      name=i->first;
      equation=i->second;
      v=ToVector(equation);
      cout<<"EQUATION "<<equation<<'\n';
      v=test3(v);
    }
}
