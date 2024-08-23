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

  Bools(const string &s1, const string &s2, const Data &data)
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

Equation *CreateNewValueValueMathOperation(const string &s1, const string &s2, const string &o, const unsigned int k, Bools b)
{
  Equation *m=new Equation;

  if(b.s1_variable and b.s2_variable)
    {
      cout<<"s1_variable and s2_variable"<<'\n';
      m->m1=CreateNewMathOperation<Variable, Variable, VariableVariable>(s1, s2, o, k);
    }
  else if(b.s1_variable and b.s2_constant)
    {
      cout<<"s1_variable and s2_constant"<<'\n';
      m->m1=CreateNewMathOperation<Variable, Constant, ConstantVariable>(s1, s2, o, k);
    }
  else if(b.s1_variable and b.s2_numeric)
    {
      cout<<"s1_variable and s2_numeric"<<'\n';
      m->m1=CreateNewMathOperation<Variable, Numeric, NumericVariable>(s1, s2, o, k);
    }
  else if(b.s1_constant and b.s2_variable)
    {
      cout<<"s1_constant and s2_variable"<<'\n';
      m->m1=CreateNewMathOperation<Constant, Variable, ConstantVariable>(s1, s2, o, k);
    }
  else if(b.s1_constant and b.s2_constant)
    {
      cout<<"s1_constant and s2_constant"<<'\n';
      m->m1=CreateNewMathOperation<Constant, Constant, ConstantConstant>(s1, s2, o, k);
    }
  else if(b.s1_constant and b.s2_numeric)
    {
      cout<<"s1_constant and s2_numeric"<<'\n';
      m->m1=CreateNewMathOperation<Constant, Numeric, NumericConstant>(s1, s2, o, k);
    }
  else if(b.s1_numeric and b.s2_variable)
    {
      cout<<"s1_numeric and s2_variable"<<'\n';
      m->m1=CreateNewMathOperation<Numeric, Variable, NumericVariable>(s1, s2, o, k);
    }
  else if(b.s1_numeric and b.s2_constant)
    {
      cout<<"s1_numeric and s2_constant"<<'\n';
      m->m1=CreateNewMathOperation<Numeric, Constant, NumericConstant>(s1, s2, o, k);
    }
  else if(b.s1_numeric and b.s2_numeric)
    {
      cout<<"s1_numeric and s2_numeric "<<'\n';
      m->m1=CreateNewMathOperation<Numeric, Numeric, NumericNumeric>(s1, s2, o, k);
      // Result of numeric-numeric math operation can be calculated in advance, so the equation template can
      // simplified and performance of the calculation increased.
      m->m1->CalculateResult();
    }
  // m->id=k;
  return m;
}

Equation *Val2(Equation *&e, const vector<string> &equation, const unsigned int i, const Data &data, const unsigned int &k, Equation *&next)
{
  Equation *mc;
  const string s1=equation[i-1];
  const string s2=equation[i+1];
  const string o=equation[i];
  const Bools b(s1, s2, data);

  cout<<"Math operation "<<'\n';
  cout<<"   "<<"v"<<" "<<"c"<<" "<<"n"<<" "<<"m"<<'\n';
  cout<<"s1 "<<b.s1_variable<<" "<<b.s1_constant<<" "<<b.s1_numeric<<" "<<b.s1_math<<'\n';
  cout<<"s2 "<<b.s2_variable<<" "<<b.s2_constant<<" "<<b.s2_numeric<<" "<<b.s2_math<<'\n';

  if(!b.s1_math and !b.s2_math)
    {
      mc=CreateNewValueValueMathOperation(s1, s2, o, k, b);
      mc->id=k;
      cout<<"!b.s1_math and !b.s2_math "<<mc<<" "<<mc->id<<" "<<next<<'\n';
      return mc;
    }
  else if(b.s1_variable and b.s2_math)
    {
      cout<<"s1_variable and s2_math "<<next<<'\n';
      return NewMathValue<Variable, VEquation>(s2, s1, o, k, e, next);
    }
  else if(b.s1_constant and b.s2_math)
    {
      cout<<"s1_constant and s2_math"<<'\n';
      return NewMathValue<Constant, VEquation>(s2, s1, o, k, e, next);
    }
  else if(b.s1_numeric and b.s2_math)
    {
      cout<<"s1_numeric and s2_math"<<'\n';
      return NewMathValue<Numeric, VEquation>(s2, s1, o, k, e, next);
    }
  else if(b.s1_math and b.s2_variable)
    {
      cout<<"s1_math and s2_variable "<<next<<'\n';
      return NewMathValue<Variable, EquationV>(s1, s2, o, k, e, next);
    }
  else if(b.s1_math and b.s2_constant)
    {
      cout<<"s1_math and s2_constant"<<'\n';
      return NewMathValue<Constant, EquationV>(s1, s2, o, k, e, next);
    }
  else if(b.s1_math and b.s2_numeric)
    {
      cout<<"s1_math and s2_numeric"<<'\n';
      return NewMathValue<Numeric, EquationV>(s1, s2, o, k, e, next);
    }
  else if(b.s1_math and b.s2_math)
    {
      cout<<"s1_math and s2_math"<<'\n';
      EquationOp *mc2=new EquationOp;
      mc2->id=k;
      Equation *m1=Search(e, stoi(s1.substr(1, s1.size())));
      Equation *m2=Search(e, stoi(s2.substr(1, s2.size())));
  //     cout<<"m1 "<<m1<<" m2 "<<m2<<'\n';
      const double result1=m1->result;
      const double result2=m2->result;
      const bool r1_null=isnan(result1);
      const bool r2_null=isnan(result2);

      if(!r1_null and !r2_null)
	{
	  cout<<"!r1_null and !r2_null"<<'\n';
	  // m1->Calculate();
	  // m2->Calculate();
	  mc2->SetOperator(o);
	  mc2->math_operator->Calculate1(result1, result2);
	  delete m1;
	  delete m2;

  // 	  NumericNumeric *n=new NumericNumeric;
  // 	  n->SetV1(new Numeric(result1));
  // 	  n->SetV2(new Numeric(result2));
  // 	  n->CalculateResult();
  // 	  m->SetTotalOperator(o);
  // 	  m->total_result=n->result;
  // 	  delete n;
  // 	  m->SetV1(nullptr);
  // 	  m->SetV2(nullptr);
  // 	  m->SetOp(nullptr);
	}
      else if(r1_null and !r2_null)
	{
	  cout<<"r1_null and !r2_null"<<'\n';
  // 	  // Result is not known at this point.
  // 	  m->SetV1(m1->GetV1()->New(m1->GetV1()));
  // 	  m->SetV2(m1->GetV2()->New(m1->GetV2()));
  // 	  m->SetOp(m1->GetOp()->New());
  // 	  m->SetV12(nullptr);
  // 	  m->SetV22(nullptr);
  // 	  m->SetOperator2(nullptr);
  // 	  // Since the result is already known, V1, V2 and math_operator are not relevant.
  // 	  m->result2=result2;
  // 	  m->SetTotalOperator(o);
	}
      else if(!r1_null and r2_null)
	{
  // 	  cout<<"!r1_null and r2_null"<<'\n';
  // 	  // Since the result is already known, V1, V2 and math_operator are not relevant, thus they can be set to nullptr.
  // 	  m->SetV1(nullptr);
  // 	  m->SetV2(nullptr);
  // 	  m->SetOp(nullptr);
  // 	  m->result=result1;
  // 	  m->SetV12(m2->GetV1()->New(m2->GetV1()));
  // 	  m->SetV22(m2->GetV2()->New(m2->GetV2()));
  // 	  m->SetOperator2(m2->GetOp()->New());
  // 	  m->SetTotalOperator(o);
	}
      else
	{
	  cout<<"else"<<'\n';
	  // mc2->m1=m1;
	  // mc2->m2=m2;
	  m1->Type();
	  m2->Type();

  // 	  // Get math operation 1 containing V1, V2 and math operation 1
  // 	  m->SetV1(m1->GetV1()->New(m1->GetV1()));
  // 	  m->SetV2(m1->GetV2()->New(m1->GetV2()));
  // 	  m->SetOp(m1->GetOp()->New());
  // 	  // Get math operation 2 containing V1, V2 and math operation 2
  // 	  m->SetV12(m2->GetV1()->New(m2->GetV1()));
  // 	  m->SetV22(m2->GetV1()->New(m2->GetV1()));
  // 	  m->SetOperator2(m2->GetOp()->New());
  // 	  // Total math operator
  // 	  m->SetTotalOperator(o);
	}
      m1->next=nullptr;
      m2->next=nullptr;
      next=nullptr;
      delete m1;
      delete m2;
      // cout<<"moperator "<<m<<" nxt "<<m->next<<'\n';
      // cout<<"mopertor "<<m<<" "<<m->GetV1()<<" "<<m->GetOp()<<" "<<m->GetV2()<<" "<<m->GetV12()<<" "<<m->GetV22()<<" "<<m->GetOp()<<'\n';
      // return m;
      return mc2;
    }
  // else if(!s1_variable && !s1_constant && !s1_numeric && !s1_math)
  //   {
  //     throw std::invalid_argument("Value \""+s1+"\" is not a constant, variable/compartment or numeric value.");
  //   }
  // else
  //   {
  //     throw std::invalid_argument("Value \""+s2+"\" is not a constant, variable/compartment or numeric value.");
  //   }
}

vector<string> FindOperator(vector<string> equation, const string &find, unsigned int &k, const Data &data, Equation *&e, Equation *&next)
{
  unsigned int i=0;

  while(i<equation.size())
    {
      if(find==equation[i])
	{
	  cout<<"Adding "<<"@"+to_string(k)<<"="<<equation[i-1]<<equation[i]<<equation[i+1]<<" "<<'\n';
	  e=Val2(e, equation, i, data, k, next);

	  e->next=next;

	  next=e;

	  cout<<"next "<<next<<'\n';

	  equation[i]="@"+to_string(k);
	  equation.erase(equation.begin()+i+1);
	  equation.erase(equation.begin()+i-1);

	  k++;
	  i=0;
	  cout<<" "<<'\n';
	  continue;
	}
      i++;
    }
  return equation;
}

void GetOrder(vector<string> &equation, unsigned int &k, const Data &data, Equation *&e, Equation *&next)
{
  for(const auto&i: OPERATORS)
    {
      // if(equation.size()<=1) break;
      equation=FindOperator(equation, i, k, data, e, next);
    }
}

vector<string> RemoveOpenClose(vector<string> equation)
{
  // Removes unnecessary parenthesis from equations such as ((1+(a+b)))
  const unsigned int open=distance(equation.begin(), find(equation.begin(), equation.end(), OPEN));
  const unsigned int close=distance(equation.begin(), find(equation.begin(), equation.end(), CLOSE));
  if(open!=equation.size() and close!=equation.size()) equation=Remove(equation, open, close);
  return equation;
}

vector<string> GetParenthesis(const vector<string> &equation, const int &open, const int &close, unsigned int &k, const Data &data, Equation *&e, Equation *&next, EquationStruct &eq)
{
  vector<string> v1{equation.begin()+open+1, equation.begin()+close};
  GetOrder(v1, k, data, e, next);
  v1=test(v1, k, data, e, next, eq);
  const vector<string> v2{equation.begin(), equation.begin()+open};
  const vector<string> v3{equation.begin()+close+1, equation.end()};
  vector<string> result;
  result.reserve(v1.size()+v2.size()+v3.size());
  result.insert(result.begin(), v2.begin(), v2.end());
  result.insert(result.end(), v1.begin(), v1.end());
  result.insert(result.end(), v3.begin(), v3.end());
  print_vector2(result);

  // eq.equation=result;

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

  EquationStruct eq;
  vector<string> v;
  unsigned int k=0;
  Equation *e=nullptr;
  Equation *next=nullptr;

  for(const auto& [name, equation]: equations_map)
    {
      v=ToVector(equation);
      v=RemoveOpenClose(v);

      eq.equation=v;

      cout<<"EQUATION"<<'\n';
      print_vector2(v);
      cout<<" "<<'\n';
      v=test(v, k, data, e, next, eq);
      GetOrder(v, k, data, e, next);

      Print(e);
      next=nullptr;
      k=0;
      cout<<"ok"<<'\n';
      cout<<" "<<'\n';
    }
}
