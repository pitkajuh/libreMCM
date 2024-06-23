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
#include "../types/Value.h"
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

// bool IsNumerical(const string &s)
// {
//   bool r=false;
//   for(const auto &i: s)
//     if(isdigit(i))
//       {
// 	r=true;
//       }
//   return r;
// }

bool IsConstant(const string &s, const unordered_map<string, string> &constants_map)
{
  bool r=false;
  return r;
}

bool IsVariable(const string &s, const vector<string> &diagonal)
{
  bool r=false;
  return r;
}

vector<string> FindOperator(vector<string> &equation, const string &find, unsigned int &k)
{
  unsigned int i=0;
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
  return equation;
}

vector<string> GetOrder(vector<string> equation, unsigned int &k)
{
  for(const auto&i: OPERATORS) equation=FindOperator(equation, i, k);
  return equation;
}

vector<string> RemoveOpenClose(vector<string> equation)
{
  // Removes unnecessary parenthesis from equations such as ((1+(a+b)))
  const unsigned int open=distance(equation.begin(), find(equation.begin(), equation.end(), OPEN));
  const unsigned int close=distance(equation.begin(), find(equation.begin(), equation.end(), CLOSE));
  if(open!=equation.size() and close!=equation.size())  equation=Remove(equation, open, close);
  return equation;
}

vector<string> GetParenthesis(const vector<string> equation, const int open, const int close, unsigned int &k)
{
  vector<string> tmp={equation.begin()+open+1, equation.begin()+close};
  tmp=test(tmp, k);
  tmp=GetOrder(tmp, k);
  vector<string> tmp4;
  const vector<string> tmp2={equation.begin(), equation.begin()+open};
  const vector<string> tmp3={equation.begin()+close+1, equation.end()};
  tmp4.insert(tmp4.begin(), tmp2.begin(), tmp2.end());
  tmp4.insert(tmp4.end(), tmp.begin(), tmp.end());
  tmp4.insert(tmp4.end(), tmp3.begin(), tmp3.end());
  return tmp4;
}

void ParseEquations(const unordered_map<string, string> equations_map)
{
    // Set calculation order of  an equation according to order of operations:

    // 1. Parentheses
    // 2. Exponents
    // 3. Multiplication and division
    // 4. Addition and subtraction

  vector<string> v;
  unsigned int k=0;

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
      v=test(v, k);
      v=GetOrder(v, k);
      cout<<" "<<'\n';
    }
}
