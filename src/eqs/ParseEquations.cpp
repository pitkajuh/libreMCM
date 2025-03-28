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

// struct Bools
// {
// public:
//   bool variable;
//   bool constant;
//   bool numeric;
//   bool math;

//   Bools(const string &s1, const vector<string> &data)
//   {
//     variable=IsIn(s1, data);
//     numeric=IsNumerical(s1);
//     math=(s1.substr(0, 1)=="@") ? 1 : 0;
//     if(!variable and !numeric and !math) constant=1;
//     else constant=0;
//   }
// };

MathOperation *CreateNewValueValueMathOperation(const string &s1, const string &s2, const string &o, const Bools &b1, const Bools &b2, GraphEquation *&graph)
{
  if(b1.variable and b2.variable)
    {
      return CreateNewMathOperation<Variable, Variable, VariableVariable>(s1, s2, o);
    }
  else if(b1.variable and b2.constant)
    {
      return CreateNewMathOperation<Variable, Constant, VariableConstant>(s1, s2, o);
    }
  else if(b1.variable and b2.numeric)
    {
      return CreateNewMathOperation<Variable, Numeric, VariableNumeric>(s1, s2, o);
    }
  else if(b1.constant and b2.variable)
    {
      return CreateNewMathOperation<Constant, Variable, ConstantVariable>(s1, s2, o);
    }
  else if(b1.constant and b2.constant)
    {
      return CreateNewMathOperation<Constant, Constant, ConstantConstant>(s1, s2, o);
    }
  else if(b1.constant and b2.numeric)
    {
      return CreateNewMathOperation<Constant, Numeric, ConstantNumeric>(s1, s2, o);
    }
  else if(b1.numeric and b2.variable)
    {
      return CreateNewMathOperation<Numeric, Variable, NumericVariable>(s1, s2, o);
    }
  else if(b1.numeric and b2.constant)
    {
      return CreateNewMathOperation<Numeric, Constant, NumericConstant>(s1, s2, o);
    }
  else
    {
      MathOperation *m=CreateNewMathOperation<Numeric, Numeric, NumericNumeric>(s1, s2, o);
      // Result of numeric-numeric math operation can be calculated in advance, so the equation template can
      // simplified and performance of the calculation increased.
      m->Calculate();
      cout<<"result "<<m->result<<'\n';
      return m;
    }
}

void ChangeHeadNode(Equation *&head, EquationMath *&newnode, Equation *node1, Equation *&node2, const uint8_t deltaid)
{
  cout<<"node2->next=node1->next; "<<node2->next<<" "<<node1->next<<'\n';
  node2->next=node1->next;

  if(deltaid>1) newnode->next=Search2(head, node2);
  else newnode->next=node2->next;
}

void SelectNode(Equation *&head, EquationMath *&newnode, Equation *node1, Equation *&node2)
{
  Select(head, node2, newnode);
  Select(head, node1, newnode);
  printeq(newnode);
}

void CreateNewNode(Equation *&head, EquationMath *&newnode, const uint8_t id, const uint8_t nodeid1, const uint8_t nodeid2)
{
  if(nodeid1<nodeid2) ChangeHeadNode(head, newnode, newnode->GetM1(), newnode->GetM2(), id-nodeid2);
  else ChangeHeadNode(head, newnode, newnode->GetM2(), newnode->GetM1(), id-nodeid1);
}

void CreateNewNode2(Equation *&head, EquationMath *&newnode, const uint8_t id, const uint8_t nodeid1, const uint8_t nodeid2)
{
  if(nodeid1>nodeid2) SelectNode(head, newnode, newnode->GetM1(), newnode->GetM2());
  else SelectNode(head, newnode, newnode->GetM2(), newnode->GetM1());
}

Equation *CreateNewMathMath(const string &s1, const string &s2, const string &o, const uint8_t id, Equation *&head)
{
  EquationMath *newhead=new EquationMath;
  newhead->SetOperator(o);
  newhead->SetId(id);
  const uint8_t s1i=stoi(s1.substr(1, s1.size()));
  const uint8_t s2i=stoi(s2.substr(1, s2.size()));
  const uint8_t delta=(s2i>s1i) ? s2i-s1i: s1i-s2i;
  newhead->Set(Search(head, s1i), Search(head, s2i));

  printeq(head);

  if(delta==1) CreateNewNode(head, newhead, id, s1i, s2i);
  else CreateNewNode2(head, newhead, id, s1i, s2i);

  printeq(newhead);
  return newhead;
}

Equation *Val2(Equation *&head, const vector<string> &equation, const uint8_t i, const vector<string> &data, const uint8_t id, Equation *&next, GraphEquation *&graph)
{
  const string s1=equation[i-1];
  const string s2=equation[i+1];
  const string o=equation[i];
  const Bools b1(s1, data);
  const Bools b2(s2, data);

  cout<<"Math operation "<<'\n';
  cout<<"   "<<"v"<<" "<<"c"<<" "<<"n"<<" "<<"m"<<'\n';
  cout<<"s1 "<<b1.variable<<" "<<b1.constant<<" "<<b1.numeric<<" "<<b1.math<<'\n';
  cout<<"s2 "<<b2.variable<<" "<<b2.constant<<" "<<b2.numeric<<" "<<b2.math<<'\n';

  if(!b1.math and !b2.math)
    {
      EquationMulti *mc=new EquationMulti;
      cout<<"!b1.math and !b2.math"<<'\n';
      mc->SetMathOperation(CreateNewValueValueMathOperation(s1, s2, o, b1, b2, graph));
      mc->Calculate();
      mc->next=next;
      mc->SetId(id);
      return mc;
    }
  else if(b1.variable and b2.math) return NewMathValue<Variable, VEquationVariable>(s2, s1, o, id, head,  next);
  else if(b1.constant and b2.math) return NewMathValue<Constant, VEquationConstant>(s2, s1, o, id, head, next);
  else if(b1.numeric and b2.math) return NewMathValue<Numeric, VEquationNumerical>(s2, s1, o, id, head, next);
  else if(b1.math and b2.variable) return NewMathValue<Variable, EquationVVariable>(s1, s2, o, id, head, next);
  else if(b1.math and b2.constant) return NewMathValue<Constant, EquationVConstant>(s1, s2, o, id, head, next);
  else if(b1.math and b2.numeric) return NewMathValue<Numeric, EquationVNumerical>(s1, s2, o, id, head, next);
  else if(b1.math and b2.math) return CreateNewMathMath(s1, s2, o, id, head);
  else if(!b1.variable and !b1.constant and !b1.numeric and !b1.math) throw std::invalid_argument("Value \""+s1+"\" is not a constant, variable/compartment or numeric value.");
  else throw std::invalid_argument("Value \""+s2+"\" is not a constant, variable/compartment or numeric value.");
}

void FindOperator(vector<string> &equation, const string &find, uint8_t &id, const vector<string> &data, Equation *&head, Equation *&next, GraphEquation *&graph)
{
  const uint8_t i=distance(equation.begin(), std::find(equation.begin(), equation.end(), find));

  if(i<equation.size())
    {
      cout<<"Adding "<<"@"+to_string(id)<<"="<<equation[i-1]<<equation[i]<<equation[i+1]<<" "<<'\n';
      head=Val2(head, equation, i, data, id, next, graph);

      head->GetType();
      printeq(head);


      next=head;
      // cout<<"head "<<head->next<<'\n';
      // next=head->next;
      // cout<<"head "<<next<<'\n';
      printeq(head);

      equation[i]="@"+to_string(id);
      equation.erase(equation.begin()+i+1);
      equation.erase(equation.begin()+i-1);

      print_vector2(equation);
      id++;
      FindOperator(equation, find, id, data, head, next, graph);
    }
}

// Equation *CreateSingleEquation(const string &e, uint8_t &id, const vector<string> &data, Equation *&next, GraphEquation *&graph)
// {
//   const Bools b(e, data);
//   EquationSingle *newHead=new EquationSingle;
//   MathOperationBase *m;
//   newHead->next=next;
//   newHead->SetId(id);
//   cout<<"Single"<<'\n';

//   if(b.variable)
//     {
//       m=new VariableBase;
//       m->SetV1(new Variable(e));
//     }
//   else if(b.constant)
//     {
//       m=new ConstantBase;
//       m->SetV1(new Constant(e));
//     }
//   else
//     {
//       m=new NumericBase;
//       m->SetV1(new Numeric(e));
//     }

//   graph=new GraphEquationSingle(b, e);
//   newHead->SetMathOperation(m);
//   return newHead;
// }

void ParseOperators(vector<string> &equation, uint8_t &id, const vector<string> &data, Equation *&head, Equation *&next, const uint8_t size, GraphEquation *&graph)
{
  for(const auto&i: OPERATORS)
    {
      if(size<2) break;
      FindOperator(equation, i, id, data, head, next, graph);
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

vector<string> GetParenthesis(const vector<string> &equation, const uint8_t open, const uint8_t close, uint8_t &id, const vector<string> &data, Equation *&head, Equation *&next, GraphEquation *&graph)
{
  vector<string> v1{equation.begin()+open+1, equation.begin()+close};
  ParseOperators(v1, id, data, head, next, v1.size(), graph);
  v1=test(v1, id, data, head, next, graph);
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

void GetOrder(vector<string> &equation, uint8_t &id, const vector<string> &data, Equation *&head, Equation *&next, GraphEquation *&graph)
{
  const uint8_t size=equation.size();

  if(size==1)
    {
      const Bools b(equation[0], data);
      graph=new GraphEquationSingle(b, equation[0], id);
      // head=CreateSingleEquation(equation[0], id, data, next, graph);
    }
  else
    {
      equation=test(equation, id, data, head, next, graph);
      ParseOperators(equation, id, data, head, next, size, graph);
    }
}

Map<string, Equation*> ParseEquations(const SMap &equations_map, const vector<string> &data)
{
  // Set calculation order of an equation according to order of operations:

  // 1. Parentheses
  // 2. Exponents
  // 3. Multiplication and division
  // 4. Addition and subtraction

  vector<string> v;
  uint8_t id=0;
  Equation *head=nullptr;
  Equation *next=nullptr;
  Map<string, Equation*> equationMap;



  // Value *v11=new Constant;
  // v11->SetName("aoe");
  // Value *v22=new Constant(*v11);

  // cout<<"value "<<v11<<" "<<v22<<'\n';
  // cout<<"value "<<v11->GetName()<<" "<<v22->GetName()<<'\n';

  // MathOperation *mb1=new ConstantConstant;
  // mb1->SetV1(v11);
  // mb1->SetV2(v22);
  // string plus="+";
  // mb1->SetOperator(plus);
  // cout<<"mb1 "<<mb1<<'\n';
  // MathOperation *mb2=new ConstantConstant(*mb1);

  // cout<<"mb2 "<<mb2<<'\n';

  // EquationMulti *eq=new EquationMulti;
  // eq->SetMathOperation(mb1);

  // EquationMulti *eq2=new EquationMulti(*eq);
  // // eq2->SetMathOperation(mb2);

  // // delete mb1;
  // delete mb2;
  // delete eq;
  // delete eq2;

  GraphEquation *graphEquation=nullptr;

  for(const auto& [name, equation]: equations_map)
    {
      v=ToVector(equation);
      v=RemoveOpenClose(v);
      cout<<"EQUATION"<<'\n';
      print_vector2(v);
      GetOrder(v, id, data, head, next, graphEquation);

      printeq(head);
      // head->next=nullptr;
      equationMap[name]=head;
      next=nullptr;
      id=0;
      delete graphEquation;
      cout<<"ok"<<'\n';

      cout<<" "<<'\n';
    }
  return equationMap;
}
