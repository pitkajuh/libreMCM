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

EquationOperation *CreateNewValueValueMathOperation(const string &s1, const string &s2, const string &o, const Bools &b)
{
  EquationOperation *m=new EquationOperation;

  if(b.s1_variable and b.s2_variable)
    {
      // cout<<"s1_variable and s2_variable"<<'\n';
      m->m1=CreateNewMathOperation<Variable, Variable, VariableVariable>(s1, s2, o);
    }
  else if(b.s1_variable and b.s2_constant)
    {
      // cout<<"s1_variable and s2_constant"<<'\n';
      m->m1=CreateNewMathOperation<Variable, Constant, ConstantVariable>(s1, s2, o);
    }
  else if(b.s1_variable and b.s2_numeric)
    {
      // cout<<"s1_variable and s2_numeric"<<'\n';
      m->m1=CreateNewMathOperation<Variable, Numeric, NumericVariable>(s1, s2, o);
    }
  else if(b.s1_constant and b.s2_variable)
    {
      // cout<<"s1_constant and s2_variable"<<'\n';
      m->m1=CreateNewMathOperation<Constant, Variable, ConstantVariable>(s1, s2, o);
    }
  else if(b.s1_constant and b.s2_constant)
    {
      // cout<<"s1_constant and s2_constant"<<'\n';
      m->m1=CreateNewMathOperation<Constant, Constant, ConstantConstant>(s1, s2, o);
    }
  else if(b.s1_constant and b.s2_numeric)
    {
      // cout<<"s1_constant and s2_numeric"<<'\n';
      m->m1=CreateNewMathOperation<Constant, Numeric, NumericConstant>(s1, s2, o);
    }
  else if(b.s1_numeric and b.s2_variable)
    {
      // cout<<"s1_numeric and s2_variable"<<'\n';
      m->m1=CreateNewMathOperation<Numeric, Variable, NumericVariable>(s1, s2, o);
    }
  else if(b.s1_numeric and b.s2_constant)
    {
      // cout<<"s1_numeric and s2_constant"<<'\n';
      m->m1=CreateNewMathOperation<Numeric, Constant, NumericConstant>(s1, s2, o);
    }
  else if(b.s1_numeric and b.s2_numeric)
    {
      // cout<<"s1_numeric and s2_numeric "<<'\n';
      m->m1=CreateNewMathOperation<Numeric, Numeric, NumericNumeric>(s1, s2, o);
      // Result of numeric-numeric math operation can be calculated in advance, so the equation template can
      // simplified and performance of the calculation increased.
      m->Calculate();
      cout<<"result "<<m->result<<'\n';
    }
  return m;
}

Equation *CreateNewMathMath(const string &s1, const string &s2, const string &o, const unsigned &k, Equation *&e, Equation *&next, const unsigned &size)
{
  const unsigned s1i=stoi(s1.substr(1, s1.size()));
  const unsigned s2i=stoi(s2.substr(1, s2.size()));
  // Equation *m1=Search(e, s1i);
  // Equation *m2=Search(e, s2i);

  // cout<<"next "<<next<<'\n';
  // cout<<s1i<<" m1 "<<m1<<" m1->next "<<m1->next<<'\n';
  // cout<<s2i<<" m2 "<<m2<<" m2->next "<<m2->next<<'\n';

  // //     cout<<"m1 "<<m1<<" m2 "<<m2<<'\n';
  // const double result1=m1->result;
  // const double result2=m2->result;
  // const bool r1_null=isnan(result1);
  // const bool r2_null=isnan(result2);

  EquationMath *mc12=new EquationMath;
  mc12->SetOperator(o);
  mc12->id=k;





  mc12->m11=Search(e, s1i);
  mc12->m21=Search(e, s2i);
  // mc12->m11=m1;
  // mc12->m21=m2;
  // cout<<"mc12 "<<mc12<<'\n';

  // if(s1i>s2i)
  //   {
  //     cout<<"m1 "<<m1->next<<" "<<'\n';
  //     if((m1->next!=nullptr))
  // 	{
  // 	  mc12->next=m1->next;
  // 	  // m1->next=nullptr;
  // 	}
  //     else mc12->next=next;

  //   }
  // else
  //   {
  //     cout<<"m2 "<<" "<<m2->next<<" "<<next<<'\n';
  //     if((m2->next!=nullptr))
  // 	{
  // 	  mc12->next=m2->next;
  // 	  // m2->next=nullptr;
  // 	}
  //     else  mc12->next=next;

  //   }

  // mc12->m11->next=nullptr;
  // mc12->m21->next=nullptr;

  if(size>3)
    {
      cout<<"size>3 mc12->next=next "<<next<<'\n';
      mc12->next=next;
      // mc12->m11->next=nullptr; //NO
        // mc12->m21->next=nullptr;
    }
  else
    {
      cout<<"size<3 mc12->next=nullptr"<<'\n';
      mc12->next=nullptr;
      mc12->m21->next=nullptr;
      // mc12->m11->next=nullptr;
      // next=nullptr;
    }




  // next->next=nullptr;

  // mc12->next=next;

  cout<<"mc12 "<<mc12<<" mc12->next "<<mc12->next<<" "<<size<<'\n';
  return mc12;

  // if(!r1_null and !r2_null)
  //   {
  //     // cout<<"!r1_null and !r2_null"<<'\n';
  //     // EquationOp *mc2=new EquationOp;
  //     // // mc2->next=next;
  //     // mc2->id=k;
  //     // mc2->SetOperator(o);
  //     // mc2->m1=nullptr;
  //     // mc2->m2=nullptr;
  //     // mc2->result=mc2->math_operator->Calculate1(result1, result2);
  //     // cout<<"!r1_null and !r2_null result "<<mc2->result<<'\n';
  //     // delete m1;
  //     // delete m2;
  //     // return mc2;
  //   }
  // else
  //   {
  //     cout<<"else1 "<<k<<'\n';
  //     EquationMath *mc12=new EquationMath;
  //     // EquationOp *mc12=new EquationOp;

  //     // if(s1i>s2i)
  //     // 	{
  //     // 	  if((m1->next!=nullptr)) mc12->next=m1->next;
  //     // 	  else mc12->next=next;
  //     // 	}
  //     // else
  //     // 	{
  //     // 	  if((m2->next!=nullptr)) mc12->next=m2->next;
  //     // 	  else  mc12->next=next;
  //     // 	}
  //     // cout<<"mc12->next "<<mc12->next<<'\n';
  //     // mc12->id=k;
  //     mc12->SetOperator(o);
  //     mc12->m1=m1;
  //     mc12->m2=m2;
  //     // cout<<"mc12 "<<mc12<<'\n';
  //     return mc12;
  //   }
}

Equation *Val2(Equation *&e, const vector<string> &equation, const unsigned i, const Data &data, const unsigned &k, Equation *&next)
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
      // cout<<"!b.s1_math and !b.s2_math "<<'\n';
      return mc;
    }
  else if(b.s1_variable and b.s2_math)
    {
      // cout<<"s1_variable and s2_math"<<'\n';
      return NewMathValue<Variable, ValueEquationOperation>(s2, s1, o, k, e, next, size);
    }
  else if(b.s1_constant and b.s2_math)
    {
      // cout<<"s1_constant and s2_math"<<'\n';
      return NewMathValue<Constant, ValueEquationOperation>(s2, s1, o, k, e, next, size);
    }
  else if(b.s1_numeric and b.s2_math)
    {
      // cout<<"s1_numeric and s2_math"<<'\n';
      return NewMathValue<Numeric, ValueEquationOperation>(s2, s1, o, k, e, next, size);
    }
  else if(b.s1_math and b.s2_variable)
    {
      // cout<<"s1_math and s2_variable "<<'\n';
      return NewMathValue<Variable, EquationOperationValue>(s1, s2, o, k, e, next, size);
    }
  else if(b.s1_math and b.s2_constant)
    {
      // cout<<"s1_math and s2_constant"<<'\n';
      return NewMathValue<Constant, EquationOperationValue>(s1, s2, o, k, e, next, size);
    }
  else if(b.s1_math and b.s2_numeric)
    {
      // cout<<"s1_math and s2_numeric"<<'\n';
      return NewMathValue<Numeric, EquationOperationValue>(s1, s2, o, k, e, next, size);
    }
  else if(b.s1_math and b.s2_math)
    {
      // cout<<"s1_math and s2_math "<<'\n';
      return CreateNewMathMath(s1, s2, o, k, e, next, size);
    }
  else if(!b.s1_variable && !b.s1_constant && !b.s1_numeric && !b.s1_math)
    {
      throw std::invalid_argument("Value \""+s1+"\" is not a constant, variable/compartment or numeric value.");
    }
  else
    {
      throw std::invalid_argument("Value \""+s2+"\" is not a constant, variable/compartment or numeric value.");
    }
}

vector<string> FindOperator(vector<string> equation, const string &find, unsigned &k, const Data &data, Equation *&e, Equation *&next)
{
  unsigned i=0;
  unsigned size=equation.size();

  while(i<size)
    {
      if(find==equation[i])
	{
	  cout<<"Adding "<<"@"+to_string(k)<<"="<<equation[i-1]<<equation[i]<<equation[i+1]<<" "<<'\n';
	  e=Val2(e, equation, i, data, k, next);
	  // e->next=next;
	  cout<<"e="<<e<<" next "<<e->next<<'\n';
	  next=e;

	  equation[i]="@"+to_string(k);
	  equation.erase(equation.begin()+i+1);
	  equation.erase(equation.begin()+i-1);
	  print_vector2(equation);
	  // cout<<"next "<<next<<" "<<next->id<<'\n';
	  size=equation.size();
	  // cout<<"size "<<size<<'\n';
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
      // if(equation.size()<=1) break;
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

vector<string> GetParenthesis(const vector<string> &equation, const int &open, const int &close, unsigned &k, const Data &data, Equation *&e, Equation *&next, EquationStruct &eq)
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
  unsigned k=0;
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
      e->next=nullptr;
      Print(e);
      next=nullptr;
      k=0;
      cout<<"ok"<<'\n';
      cout<<" "<<'\n';
    }
}
