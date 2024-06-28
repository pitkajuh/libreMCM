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
using MathOperations=vector<OpTmp>;

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
  MathOperations operation;
  Eq(){}
  Eq(const vector<string> &e, const MathOperations &o)
  {
    eq=e;
    operation=o;
  }
};

vector<string> FindOperator(vector<string> equation, const string &find, unsigned int &k, MathOperations &ooo)
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
  // cout<<"end"<<'\n';
  return equation;
}

Eq GetOrder(vector<string> &equation, unsigned int &k, MathOperations &ooo)
{
  for(const auto&i: OPERATORS) equation=FindOperator(equation, i, k, ooo);
  return {equation, ooo};
}

vector<string> RemoveOpenClose(vector<string> equation)
{
  // Removes unnecessary parenthesis from equations such as ((1+(a+b)))
  const unsigned int open=distance(equation.begin(), find(equation.begin(), equation.end(), OPEN));
  const unsigned int close=distance(equation.begin(), find(equation.begin(), equation.end(), CLOSE));
  if(open!=equation.size() and close!=equation.size()) equation=Remove(equation, open, close);
  return equation;
}

vector<string> GetParenthesis(const vector<string> &equation, const int &open, const int &close, unsigned int &k, MathOperations &ooo)
{
  vector<string> v1{equation.begin()+open+1, equation.begin()+close};
  const Eq r=GetOrder(v1, k, ooo);
  v1=test(r.eq, k, ooo);
  const vector<string> v2{equation.begin(), equation.begin()+open};
  const vector<string> v3{equation.begin()+close+1, equation.end()};
  vector<string> result;
  result.reserve(v1.size()+v2.size()+v3.size());
  result.insert(result.begin(), v2.begin(), v2.end());
  result.insert(result.end(), v1.begin(), v1.end());
  result.insert(result.end(), v3.begin(), v3.end());
  return result;
}

unordered_map<string, MathOperations> ParseEquations(const unordered_map<string, string> &equations_map)
{
    // Set calculation order of  an equation according to order of operations:

    // 1. Parentheses
    // 2. Exponents
    // 3. Multiplication and division
    // 4. Addition and subtraction

  vector<string> v;
  Eq ooo;
  unsigned int k=0;
  MathOperations op;
  unordered_map<string, MathOperations> equations_map2;
  equations_map2.reserve(equations_map.size());
  int i=1;
  for(const auto& [name, equation]: equations_map)
    {
      v=ToVector(equation);
      // cout<<"EQUATION "<<'\n';
      // print_vector2(v);
      // cout<<"1-------------"<<'\n';
      v=RemoveOpenClose(v);
      cout<<" EQUATION "<<i<<'\n';
      print_vector2(v);
      v=test(v, k, op);
      ooo=GetOrder(v, k, op);
      equations_map2[name]=op;
      k=0;
      op.clear();
      cout<<" "<<'\n';
      i++;
    }
  return equations_map2;
}
