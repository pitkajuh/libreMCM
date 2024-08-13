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

MathOperation *Search(MathOperation *m, const unsigned int i)
{
  MathOperation *c=m;

  while(c!=nullptr)
    {
      if(c->id==i) return c;
      c=c->next;
    }
  return nullptr;
}

// MathOperation *NewNMMath(const string &s1, const string &s2, const string &o, const unsigned int &k, MathOperation *&c)
// {
//   MathOperation *m=new NumericMath;
//   m->SetV1(new Numeric);
//   m->SetV1Value(stod(s1));
//   m->id=k;
//   // MathOperation *m1=Search(c, stoi(s2.substr(1, s2.size())));
//   // Value *v2=m1->GetV2()->New(m1->GetV2());
//   // m->Set(v1, o, v2);
//   // const double result=m1->result;

//   // if(result!=NAN)
//   //   {
//   //     m->SetV2Value(result);
//   //     m->Calculate();
//   //   }
//   // else
//   //   {
//   //     cout<<"else NewNMMath"<<'\n';
//   //   }
//   return m;
// }

MathOperation *NewMVMath(const string &s1, const string &s2, const string &o, const unsigned int &k, MathOperation *&c)
{
  ValueMath *m=new MathVariable;
  // ValueMath *m;
  m->SetV(new Variable(s2));
  m->id=k;
  MathOperation *r=Search(c, stoi(s1.substr(1, s1.size())));
  cout<<"v "<<r->id<<" "<<r->GetV1()<<'\n';
  const double result=r->result;
  cout<<"id "<<r->id<<'\n';
  // if(!isnan(result))
  //   {
  //     // Only result will be taken into account, v1, v2 and math_operator can be omitted.
  //     m->SetV(new Numeric(result));
  //     // m->SetVValue(result);
  //     // m->SetOperator1(o);
  //     // Check *next before deleting.
  //     delete r;
  //   }
  // else
  //   {
  cout<<"else NewNVMath"<<'\n';
  // m->SetV1(r->v1->New());
  // }


  m->SetOperator1(o);

  // m->SetV1(v->New(v));
  // m->SetV2(v->New(v));
  m->SetOperator(o);

  // delete v1;
  return m;
}

// MathOperation *NewCMMath(const string &s1, const string &s2, const string &o, const unsigned int &k, MathOperation *&c)
// {
//   Value *v1=new Constant;
//   v1->SetName(s1);
//   MathOperation *m=new ConstantMath;
//   m->id=k;
//   m->SetV1(v1);
//   const double result=Search(c, stoi(s2.substr(1, s2.size())))->result;

//   if(result!=NAN)
//     {
//       Value *v2=new Numeric;
//       v2->SetValue(result);
//       m->Set(v1, o, v2);
//     }
//   else
//     {
//       cout<<"else NewCVMath"<<'\n';
//     }
//   return m;
// }

MathOperation *Val2(MathOperation *&c, const vector<string> &equation, const unsigned int i, const Data &data, const unsigned int &k, MathOperation *&next)
{
  const string s1=equation[i-1];
  const string s2=equation[i+1];
  const string o=equation[i];
  const bool s1_variable=IsIn(s1, data.diagonal);
  const bool s1_constant=IsIn(s1, data.constants_map);
  const bool s1_numeric=IsNumerical(s1);
  const bool s1_math=(s1.substr(0, 1)=="@") ? true : false;
  const bool s2_variable=IsIn(s2, data.diagonal);
  const bool s2_constant=IsIn(s2, data.constants_map);
  const bool s2_numeric=IsNumerical(s2);
  const bool s2_math=(s2.substr(0, 1)=="@") ? true : false;
  cout<<"Math operation "<<'\n';
  cout<<"   "<<"v"<<" "<<"c"<<" "<<"n"<<" "<<"m"<<'\n';
  cout<<"s1 "<<s1_variable<<" "<<s1_constant<<" "<<s1_numeric<<" "<<s1_math<<'\n';
  cout<<"s2 "<<s2_variable<<" "<<s2_constant<<" "<<s2_numeric<<" "<<s2_math<<'\n';

  if(s1_variable and s2_variable) return CreateNewMathOperation<Variable, Variable, VariableVariable>(s1, s2, o, k);
  else if(s1_variable and s2_constant) return CreateNewMathOperation<Constant, Variable, ConstantVariable>(s2, s1, o, k);
  else if(s1_variable and s2_numeric) return CreateNewMathOperation<Numeric, Variable, NumericVariable>(s2, s1, o, k);
  else if(s1_constant and s2_variable) return CreateNewMathOperation<Constant, Variable, ConstantVariable>(s1, s2, o, k);
  else if(s1_constant and s2_constant) return CreateNewMathOperation<Constant, Constant, ConstantConstant>(s1, s2, o, k);
  else if(s1_constant and s2_numeric) return CreateNewMathOperation<Numeric, Constant, NumericConstant>(s2, s1, o, k);
  else if(s1_numeric and s2_variable) return CreateNewMathOperation<Numeric, Variable, NumericVariable>(s1, s2, o, k);
  else if(s1_numeric and s2_constant) return CreateNewMathOperation<Numeric, Constant, NumericConstant>(s1, s2, o, k);
  // else if(s1_variable and s2_math)
  //   {
  //     cout<<"s1_variable and s2_math"<<'\n';
  //     return NewMVMath(s2, s1, o, k, c);
  //   }
  // else if(s1_constant and s2_math)
  //   {
  //     cout<<"s1_constant and s2_math"<<'\n';
  //     return NewCMMath(s1, s2, o, k, c);
  //   }
  // else if(s1_numeric and s2_math)
  //   {
  //     cout<<"s1_numeric and s2_math"<<'\n';
  //     return NewNMMath(s1, s2, o, k, c);
  //   }
  else if(s1_math and s2_variable)
    {
      cout<<"s1_math and s2_variable"<<'\n';
      MathOperation *m=NewMVMath(s1, s2, o, k, c);
      return m;
    }
  // else if(s1_math and s2_constant)
  //   {
  //     cout<<"s1_math and s2_constant"<<'\n';
  //     return NewCMMath(s2, s1, o, k, c);
  //   }
  // else if(s1_math and s2_numeric)
  //   {
  //     cout<<"s1_math and s2_numeric"<<'\n';
  //     return NewNMMath(s2, s1, o, k, c);
  //   }
  else if(s1_numeric and s2_numeric)
    {
      MathOperation *m=new NumericNumeric;
      m->SetV1(new Numeric(s1));
      // m->SetV1Value(stod(s1));
      m->SetV2(new Numeric(s2));
      // m->SetV2Value(stod(s2));
      m->id=k;
      m->SetOperator(o);
      m->CalculateResult();
      return m;
    }
  else if(s1_math and s2_math)
    {
      cout<<"s1_math and s2_math"<<'\n';
      MathMath *m=new MathMath;
      m->id=k;
      MathOperation *m1=Search(c, stoi(s1.substr(1, s1.size())));
      MathOperation *m2=Search(c, stoi(s2.substr(1, s2.size())));
      const double result1=m1->result;
      const double result2=m2->result;
      const bool r1_null=isnan(result1);
      const bool r2_null=isnan(result2);

      if(!r1_null and !r2_null)
	{
	  cout<<"!r1_null and !r2_null"<<'\n';
	  NumericNumeric n;
	  n.SetV1(new Numeric(result1));
	  n.SetV2(new Numeric(result2));
	  n.CalculateResult();
	  // Value *v1=new Numeric(result1);
	  // Value *v2=new Numeric(result2);
	  // m->SetV1(new Numeric(result1));
	  // m->SetV2(new Numeric(result2));
	  m->SetTotalOperator(o);
	  // v2->SetValue(result2);
	  // m->Set(v1, o, v2);
	  m->total_result=n.result;
	}
      else if(r1_null and !r2_null)
	{
	  cout<<"r1_null and !r2_null"<<'\n';
	  // Result is not known at this point.
	  m->SetV1(m1->GetV1()->New(m1->GetV1()));
	  m->SetV2(m1->GetV2()->New(m1->GetV2()));
	  m->SetOp(m1->GetOp()->New());

	  // Since the result is already known, V1, V2 and math_operator are not relevant.
	  m->result2=result2;

	  m->SetTotalOperator(o);

	  m1->next=nullptr;
	  m2->next=nullptr;
	  next=nullptr;
	  delete m2;
	  delete m1;
	}
      else if(!r1_null and r2_null)
	{
	  cout<<"!r1_null and r2_null"<<'\n';
	  // Since the result is already known, V1, V2 and math_operator are not relevant, thus they can be set to nullptr.
	  m->SetV1(nullptr);
	  m->SetV2(nullptr);
	  m->SetOp(nullptr);
	  m->result=result1;

	  m->SetV12(m2->GetV1()->New(m2->GetV1()));
	  m->SetV22(m2->GetV2()->New(m2->GetV2()));
	  m->SetOperator2(m2->GetOp()->New());

	  m->SetTotalOperator(o);

	  m1->next=nullptr;
	  m2->next=nullptr;
	  next=nullptr;
	  delete m2;
	  delete m1;
	}
      else
	{
	  cout<<"else"<<'\n';
	  // Get math operation 1 containing V1, V2 and math operation 1
	  m->SetV1(m1->GetV1()->New(m1->GetV1()));
	  m->SetV2(m1->GetV2()->New(m1->GetV2()));
	  m->SetOp(m1->GetOp()->New());

	  // Get math operation 2 containing V1, V2 and math operation 2
	  m->SetV12(m2->GetV1()->New(m2->GetV1()));
	  m->SetV22(m2->GetV1()->New(m2->GetV1()));
	  m->SetOperator2(m2->GetOp()->New());

	  // Total math operator
	  m->SetTotalOperator(o);

	  m1->next=nullptr;
	  m2->next=nullptr;
	  next=nullptr;
	  delete m2;
	  delete m1;
	}
      return m;
    }
  else if(!s1_variable && !s1_constant && !s1_numeric && !s1_math)
    {
      throw std::invalid_argument("Value \""+s1+"\" is not a constant, variable/compartment or numeric value.");
    }
  else
    {
      throw std::invalid_argument("Value \""+s2+"\" is not a constant, variable/compartment or numeric value.");
    }
}

vector<string> FindOperator(vector<string> equation, const string &find, unsigned int &k, const Data &data, MathOperation *&e, MathOperation *&next)
{
  unsigned int i=0;
  MathOperation *m;

  while(i<equation.size())
    {
      if(find==equation[i])
	{
	  e=Val2(e, equation, i, data, k, next);
	  e->next=next;
	  cout<<"next "<<next<<'\n';
	  next=e;

	  cout<<"Adding "<<"@"+to_string(k)<<"="<<equation[i-1]<<equation[i]<<equation[i+1]<<" "<<'\n';
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

void GetOrder(vector<string> &equation, unsigned int &k, const Data &data, MathOperation *&e, MathOperation *&next)
{
  for(const auto&i: OPERATORS) equation=FindOperator(equation, i, k, data, e, next);
}

vector<string> RemoveOpenClose(vector<string> equation)
{
  // Removes unnecessary parenthesis from equations such as ((1+(a+b)))
  const unsigned int open=distance(equation.begin(), find(equation.begin(), equation.end(), OPEN));
  const unsigned int close=distance(equation.begin(), find(equation.begin(), equation.end(), CLOSE));
  if(open!=equation.size() and close!=equation.size()) equation=Remove(equation, open, close);
  return equation;
}

vector<string> GetParenthesis(const vector<string> &equation, const int &open, const int &close, unsigned int &k, const Data &data, MathOperation *&e, MathOperation *&next)
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

void Delete(MathOperation *m)
{
  MathOperation *tmp=m;
  MathOperation *nxt;
  cout<<"delete begin"<<'\n';
  while(tmp->next!=nullptr)
    {
      nxt=tmp->next;
      cout<<tmp<<'\n';
      delete tmp;
      tmp=nxt;
    }
  // tmp->next=nullptr;
  cout<<"delete end"<<'\n';
}

void ParseEquations(const SMap &equations_map, const Data &data)
{
  // Set calculation order of an equation according to order of operations:

  // 1. Parentheses
  // 2. Exponents
  // 3. Multiplication and division
  // 4. Addition and subtraction

  vector<string> v;
  unsigned int k=0;
  MathOperation *e=nullptr;
  MathOperation *next=nullptr;
  // Map<string, MathOperations> equations_map2;
  // equations_map2.reserve(equations_map.size());

  for(const auto& [name, equation]: equations_map)
    {
      v=ToVector(equation);
      v=RemoveOpenClose(v);
      cout<<"EQUATION"<<'\n';
      print_vector2(v);
        cout<<" "<<'\n';
      v=test(v, k, data, e, next);
      GetOrder(v, k, data, e, next);
      // cout<<"Deleting "<<'\n';
      delete e;
      next=nullptr;
      // Delete(e);
      // delete next;
      k=0;
      cout<<" "<<'\n';
    }
  // return equations_map2;
}
