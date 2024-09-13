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
#include "../types/MathOperation.h"
#include "../types/Equation.h"
#include "../types/Data.h"
#include "../util/IsIn.h"
#include <algorithm>
#include <iostream>
#include <cmath>

using std::to_string;
using std::cout;
using std::stod;
using std::stoi;


void print_vector2(const vector<string> &vec)
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

struct Bools
{
public:
  bool s1_variable;
  bool s1_constant;
  bool s1_numeric;
  bool s1_math;
  bool s2_variable;
  bool s2_constant;
  bool s2_numeric;
  bool s2_math;

  Bools(const string s1, const string s2, const Data &data)
  {
    s1_variable=IsIn(s1, data.diagonal);
    s1_constant=IsIn(s1, data.constants_map);
    s1_numeric=IsNumerical(s1);
    s1_math=(s1.substr(0, 1)=="@") ? true : false;
    s2_variable=IsIn(s2, data.diagonal);
    s2_constant=IsIn(s2, data.constants_map);
    s2_numeric=IsNumerical(s2);
    s2_math=(s2.substr(0, 1)=="@") ? true : false;
  }
};

EquationOperation *CreateNewValueValueMathOperation(const string s1, const string s2, const string o, const Bools &b)
{
  EquationOperation *m=new EquationOperation;

  if(b.s1_variable and b.s2_variable) m->m1=CreateNewMathOperation<Variable, Variable, VariableVariable>(s1, s2, o);
  else if(b.s1_variable and b.s2_constant) m->m1=CreateNewMathOperation<Variable, Constant, ConstantVariable>(s1, s2, o);
  else if(b.s1_variable and b.s2_numeric) m->m1=CreateNewMathOperation<Variable, Numeric, NumericVariable>(s1, s2, o);
  else if(b.s1_constant and b.s2_variable) m->m1=CreateNewMathOperation<Constant, Variable, ConstantVariable>(s1, s2, o);
  else if(b.s1_constant and b.s2_constant) m->m1=CreateNewMathOperation<Constant, Constant, ConstantConstant>(s1, s2, o);
  else if(b.s1_constant and b.s2_numeric) m->m1=CreateNewMathOperation<Constant, Numeric, NumericConstant>(s1, s2, o);
  else if(b.s1_numeric and b.s2_variable) m->m1=CreateNewMathOperation<Numeric, Variable, NumericVariable>(s1, s2, o);
  else if(b.s1_numeric and b.s2_constant) m->m1=CreateNewMathOperation<Numeric, Constant, NumericConstant>(s1, s2, o);
  else if(b.s1_numeric and b.s2_numeric)
    {
      m->m1=CreateNewMathOperation<Numeric, Numeric, NumericNumeric>(s1, s2, o);
      // Result of numeric-numeric math operation can be calculated in advance, so the equation template can
      // simplified and performance of the calculation increased.
      m->Calculate();
      cout<<"result "<<m->result<<'\n';
    }
  return m;
}

void ChangeHeadNode(Equation *&head, EquationMath *&newnode, Equation *&node1, Equation *&node2, const unsigned deltaid)
{
  node2->next=node1->next;

  if(deltaid>1) newnode->next=Search2(head, node2);
  else newnode->next=node2->next;
}

void SelectNode(Equation *&head, EquationMath *&newnode, Equation *&node1, Equation *&node2)
{
  Select(head, node2, newnode);
  Select(head, node1, newnode);
  printeq(newnode);
}

void CreateNewNode(Equation *&head, EquationMath *&newnode, Equation *&node1, Equation *&node2, const unsigned id, const unsigned nodeid1, const unsigned nodeid2)
{
  if(nodeid1<nodeid2) ChangeHeadNode(head, newnode, node1, node2, id-nodeid2);
  else ChangeHeadNode(head, newnode, node2, node1, id-nodeid1);
}

void CreateNewNode2(Equation *&head, EquationMath *&newnode, Equation *&node1, Equation *&node2, const unsigned id, const unsigned nodeid1, const unsigned nodeid2)
{
  if(nodeid1>nodeid2) SelectNode(head, newnode, node1, node2);
  else SelectNode(head, newnode, node2, node1);
}

Equation *CreateNewMathMath(const string s1, const string s2, const string o, const unsigned k, Equation *&e, Equation *&next, const unsigned size)
{
  EquationMath *mc12=new EquationMath;
  mc12->SetOperator(o);
  mc12->id=k;
  const unsigned s1i=stoi(s1.substr(1, s1.size()));
  const unsigned s2i=stoi(s2.substr(1, s2.size()));
  const unsigned delta=(s2i>s1i) ? s2i-s1i: s1i-s2i;
  Equation *m1=Search(e, s1i);
  Equation *m2=Search(e, s2i);

  printeq(e);

  if(delta==1) CreateNewNode(e, mc12, m1, m2, k, s1i, s2i);
  else CreateNewNode2(e, mc12, m1, m2, k, s1i, s2i);

  mc12->m11=m1;
  mc12->m21=m2;
  printeq(mc12);
  return mc12;
}

Equation *Val2(Equation *&e, const vector<string> &equation, const unsigned i, const Data &data, const unsigned k, Equation *&next)
{
  const string s1=equation[i-1];
  const string s2=equation[i+1];
  const string o=equation[i];
  const Bools b(s1, s2, data);
  const unsigned size=equation.size();

  cout<<"Math operation "<<'\n';
  cout<<"   "<<"v"<<" "<<"c"<<" "<<"n"<<" "<<"m"<<'\n';
  cout<<"s1 "<<b.s1_variable<<" "<<b.s1_constant<<" "<<b.s1_numeric<<" "<<b.s1_math<<'\n';
  cout<<"s2 "<<b.s2_variable<<" "<<b.s2_constant<<" "<<b.s2_numeric<<" "<<b.s2_math<<'\n';

  if(!b.s1_math and !b.s2_math)
    {
      Equation *mc=new Equation;
      mc->m1=CreateNewValueValueMathOperation(s1, s2, o, b);
      mc->next=next;
      mc->id=k;
      return mc;
    }
  else if(b.s1_variable and b.s2_math){return NewMathValue<Variable, ValueEquationOperation>(s2, s1, o, k, e,  next, size);}
  else if(b.s1_constant and b.s2_math){return NewMathValue<Constant, ValueEquationOperation>(s2, s1, o, k, e, next, size);}
  else if(b.s1_numeric and b.s2_math){return NewMathValue<Numeric, ValueEquationOperation>(s2, s1, o, k, e, next, size);}
  else if(b.s1_math and b.s2_variable){return NewMathValue<Variable, EquationOperationValue>(s1, s2, o, k, e, next, size);}
  else if(b.s1_math and b.s2_constant){return NewMathValue<Constant, EquationOperationValue>(s1, s2, o, k, e, next, size);}
  else if(b.s1_math and b.s2_numeric){return NewMathValue<Numeric, EquationOperationValue>(s1, s2, o, k, e, next, size);}
  else if(b.s1_math and b.s2_math){return CreateNewMathMath(s1, s2, o, k, e, next, size);}
  else if(!b.s1_variable && !b.s1_constant && !b.s1_numeric && !b.s1_math){throw std::invalid_argument("Value \""+s1+"\" is not a constant, variable/compartment or numeric value.");}
  else{throw std::invalid_argument("Value \""+s2+"\" is not a constant, variable/compartment or numeric value.");}
}

vector<string> FindOperator(vector<string> equation, const string find, unsigned &k, const Data &data, Equation *&e, Equation *&next)
{
  unsigned i=0;
  unsigned size=equation.size();

  while(i<size)
    {
      if(find==equation[i])
	{
	  cout<<"Adding "<<"@"+to_string(k)<<"="<<equation[i-1]<<equation[i]<<equation[i+1]<<" "<<'\n';
	  e=Val2(e, equation, i, data, k, next);

	  cout<<e->id<<" e="<<e<<" next "<<e->next<<'\n';
	  printeq(e);
	  next=e;

	  equation[i]="@"+to_string(k);
	  equation.erase(equation.begin()+i+1);
	  equation.erase(equation.begin()+i-1);
	  print_vector2(equation);

	  size=equation.size();
	  k++;
	  i=0;
	  cout<<" "<<'\n';
	  continue;
	}
      i++;
    }
  return equation;
}

void GetOrder(vector<string> &equation, unsigned &k, const Data &data, Equation *&e, Equation *&next)
{
  for(const auto&i: OPERATORS)
    {
      if(equation.size()<2) break;
      equation=FindOperator(equation, i, k, data, e, next);
    }
}

vector<string> RemoveOpenClose(vector<string> equation)
{
  // Removes unnecessary parenthesis from equations such as ((1+(a+b)))
  const unsigned open=distance(equation.begin(), find(equation.begin(), equation.end(), OPEN));
  const unsigned close=distance(equation.begin(), find(equation.begin(), equation.end(), CLOSE));
  if(open!=equation.size() and close!=equation.size()) equation=Remove(equation, open, close);
  return equation;
}

vector<string> GetParenthesis(const vector<string> &equation, const int open, const int close, unsigned &k, const Data &data, Equation *&e, Equation *&next)
{
  vector<string> v1{equation.begin()+open+1, equation.begin()+close};
  GetOrder(v1, k, data, e, next);
  v1=test(v1, k, data, e, next);
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

void Print(Equation *head)
{
  Equation *current = head;
  Equation *prev = nullptr, *next = nullptr;

  while (current != nullptr) {
    // Store next
    // if(current==nullptr) break;
    cout<<"te "<<next<<" "<<current<<'\n';
    printf("aoe\n");

    next = current->next;

    // Reverse the node pointer for the current node
    current->next = prev;
    cout<<"t "<<current<<'\n';
    // Advance the pointer one position.
    prev = current;
    delete current;
    current = next;
    if(current==nullptr) break;
  }

  // Equation *tmp=head;
  // Equation *nxt;
  // cout<<"print"<<'\n';
  // while(tmp!=nullptr)
  //   {
  //     nxt=tmp->next;
  //     cout<<"t "<<tmp<<'\n';
  //     delete tmp;
  //     tmp=nxt;
  //   }
}

void ParseEquations(const SMap &equations_map, const Data &data)
{
  // Set calculation order of an equation according to order of operations:

  // 1. Parentheses
  // 2. Exponents
  // 3. Multiplication and division
  // 4. Addition and subtraction

  vector<string> v;
  unsigned k=0;
  Equation *e=nullptr;
  Equation *next=nullptr;

  for(const auto& [name, equation]: equations_map)
    {
      v=ToVector(equation);
      v=RemoveOpenClose(v);
      cout<<"EQUATION"<<'\n';
      print_vector2(v);
      cout<<" "<<'\n';
      v=test(v, k, data, e, next);
      GetOrder(v, k, data, e, next);
      e->next=nullptr;
      Print(e);
      next=nullptr;
      k=0;
      cout<<"ok"<<'\n';
      cout<<" "<<'\n';
    }
}
