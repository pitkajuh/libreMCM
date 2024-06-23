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
#include "test.h"
#include "../global/mathconst.h"
#include "../types/MathOperation.h"
#include <unordered_map>
#include <algorithm>
#include <iostream>

using std::unordered_map;
using std::to_string;
using std::cout;

void print_vector2(vector<string> vec)
{
  int i=0;
  string empty="";

  while(i<=vec.size()-1 && vec.size()>0)
    {
      if(i==0)  empty=vec[i];
      else empty=empty+";"+vec[i];
      i++;
    }
  cout<<empty<<'\n';
}

struct Eq
{
  vector<string> eq;
  vector<OpTmp> operation;
  Eq(){}
  Eq(const vector<string> &e, const vector<OpTmp> &o)
  {
    eq=e;
    operation=o;
  }
};

vector<string> FindOperator(vector<string> equation, const string &find, unsigned int &k, vector<OpTmp> &ooo)
{
  unsigned int i=0;
  OpTmp operation;

  while(i<equation.size())
    {
      if(find==equation[i])
	{
	  operation.Set(equation[i-1], equation[i], equation[i+1]);
	  ooo.emplace_back(operation);
	  cout<<"Adding "<<"T"+to_string(k)<<"="<<equation[i-1]<<equation[i]<<equation[i+1]<<" "<<ooo.size()<<'\n';
	  equation[i]="T"+to_string(k);
	  equation.erase(equation.begin()+i+1);
	  equation.erase(equation.begin()+i-1);
	  k++;
	  i=0;
	  continue;
	}
      i++;
    }
  return equation;
}

Eq GetOrder(vector<string> equation, unsigned int &k, vector<OpTmp> &ooo)
{
  for(const auto&i: OPERATORS) equation=FindOperator(equation, i, k, ooo);
  Eq r(equation, ooo);
  // r.eq=equation;
  // r.operation=ooo;
  return r;
}

vector<string> RemoveOpenClose(vector<string> equation)
{
  // Removes unnecessary parenthesis from equations such as ((1+(a+b)))
  const unsigned int open=distance(equation.begin(), find(equation.begin(), equation.end(), OPEN));
  const unsigned int close=distance(equation.begin(), find(equation.begin(), equation.end(), CLOSE));
  if(open!=equation.size() and close!=equation.size()) equation=Remove(equation, open, close);
  return equation;
}

vector<string> GetParenthesis(const vector<string> equation, const int &open, const int &close, unsigned int &k, vector<OpTmp> &ooo)
{
  vector<string> tmp={equation.begin()+open+1, equation.begin()+close};
  Eq r=GetOrder(tmp, k, ooo);
  tmp=test(tmp, k, ooo);
  // tmp=r.eq;
  const vector<string> tmp2={equation.begin(), equation.begin()+open};
  const vector<string> tmp3={equation.begin()+close+1, equation.end()};
  vector<string> tmp4;
  tmp4.insert(tmp4.begin(), tmp2.begin(), tmp2.end());
  tmp4.insert(tmp4.end(), tmp.begin(), tmp.end());
  tmp4.insert(tmp4.end(), tmp3.begin(), tmp3.end());
  return tmp4;
}

void ParseEquations(const unordered_map<string, string> &equations_map)
{
    // Set calculation order of  an equation according to order of operations:

    // 1. Parentheses
    // 2. Exponents
    // 3. Multiplication and division
    // 4. Addition and subtraction

  vector<string> v;
  Eq ooo;
  unsigned int k=0;
  vector<OpTmp> op;

  for(const auto& [name, equation]: equations_map)
    {
      v=ToVector(equation);
      // cout<<"EQUATION "<<'\n';
      // print_vector2(v);
      // cout<<"1-------------"<<'\n';
      v=RemoveOpenClose(v);
      cout<<"EQUATION "<<'\n';
      print_vector2(v);
      cout<<"2-------------"<<'\n';
      v=test(v, k, op);
      ooo=GetOrder(v, k, op);
      k=0;
      op.clear();
      cout<<" "<<'\n';
    }
}
