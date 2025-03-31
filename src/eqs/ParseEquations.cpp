/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "CreateNewMathOperation.h"
#include "ToVector.h"
#include "test.h"
#include "../global/mathconst.h"
#include "../types/Equation.h"
#include "../types/Bools.h"
#include "../util/IsIn.h"
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cassert>
#include <cstdint>
#include "../types/Graph.h"

using std::to_string;
using std::cout;
using std::stod;
using std::stoi;

void print_vector2(const vector<string> &vec)
{
  uint8_t i=0;
  string empty="";
  const uint8_t size=vec.size();
  while(i<size)
    {
      if(i==0) empty=vec[i];
      else empty=empty+";"+vec[i];
      i++;
    }
  cout<<empty<<'\n';
}

void FindOperator(vector<string> &equation, const string &find, uint8_t &id, const vector<string> &data, GraphEquation *&graph)
{
  const uint8_t i=distance(equation.begin(), std::find(equation.begin(), equation.end(), find));

  if(i<equation.size())
    {
      const string s1=equation[i-1];
      const string s2=equation[i+1];
      const string o=equation[i];
      const Bools b1(s1, data);
      const Bools b2(s2, data);

      graph->CreateEdge(s1, s2, o, b1, b2, id);

      cout<<"Adding "<<"@"+to_string(id)<<"="<<s1<<o<<s2<<" "<<'\n';

      equation[i]="@"+to_string(id);
      equation.erase(equation.begin()+i+1);
      equation.erase(equation.begin()+i-1);

      print_vector2(equation);
      id++;
      FindOperator(equation, find, id, data, graph);
    }
}

void ParseOperators(vector<string> &equation, uint8_t &id, const vector<string> &data, const uint8_t size, GraphEquation *&graph)
{
  for(const auto &i: OPERATORS)
    {
      if(size<2) break;
      FindOperator(equation, i, id, data, graph);
    }
}

vector<string> RemoveOpenClose(vector<string> equation)
{
  // Removes unnecessary parenthesis from equations such as ((1+(a+b)))
  const uint8_t open=distance(equation.begin(), find(equation.begin(), equation.end(), OPEN));
  const uint8_t close=distance(equation.begin(), find(equation.begin(), equation.end(), CLOSE));
  if(open!=equation.size() and close!=equation.size()) equation=Remove(equation, open, close);
  return equation;
}

vector<string> GetParenthesis(const vector<string> &equation, const uint8_t open, const uint8_t close, uint8_t &id, const vector<string> &data, GraphEquation *&graph)
{
  vector<string> v1{equation.begin()+open+1, equation.begin()+close};
  ParseOperators(v1, id, data, v1.size(), graph);
  v1=test(v1, id, data, graph);
  const vector<string> v2{equation.begin(), equation.begin()+open};
  const vector<string> v3{equation.begin()+close+1, equation.end()};
  vector<string> result;
  result.reserve(v1.size()+v2.size()+v3.size());

  result.insert(result.begin(), v2.begin(), v2.end());
  result.insert(result.end(), v1.begin(), v1.end());
  result.insert(result.end(), v3.begin(), v3.end());
  print_vector2(result);
  return result;
}

void GetOrder(vector<string> &equation, uint8_t &id, const vector<string> &data, GraphEquation *&graph)
{
  const uint8_t size=equation.size();

  if(size==1)
    {
      const Bools b(equation[0], data);
      graph=new GraphEquationSingle(b, equation[0]);
    }
  else
    {
      graph=new GraphEquation;
      equation=test(equation, id, data, graph);
      ParseOperators(equation, id, data, size, graph);
    }
}

void ParseEquations(const SMap &equations_map, const vector<string> &data)
{
  // Set calculation order of an equation according to order of operations:

  // 1. Parentheses
  // 2. Exponents
  // 3. Multiplication and division
  // 4. Addition and subtraction

  vector<string> v;
  uint8_t id=0;
  GraphEquation *graphEquation=nullptr;

  for(const auto& [name, equation]: equations_map)
    {
      v=ToVector(equation);
      v=RemoveOpenClose(v);
      cout<<"EQUATION"<<'\n';
      print_vector2(v);
      GetOrder(v, id, data, graphEquation);

      // head->next=nullptr;
      // equationMap[name]=head;
      id=0;
      delete graphEquation;
      graphEquation=nullptr;
      cout<<"ok"<<'\n';

      cout<<" "<<'\n';
    }

}
