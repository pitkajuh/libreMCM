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
#include "../types/Data.h"
#include "../util/IsIn.h"
#include <algorithm>
#include <iostream>

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

MathOperation *NewNMMath(const string &s1, const string &s2, const string &o, MathOperations &op)
{
  const unsigned int s2d=stoi(s2.substr(1, s2.size()));
  Value *v1=new Numeric;
  v1->SetValue(stod(s1));
  MathOperation *m=new NMMathOperation;
  m->Init(op[s2d], v1, o);
  return m;
}

MathOperation *NewNVMath(const string &s1, const string &s2, const string &o)
{
  Value *v1=new Numeric;
  v1->SetValue((stod(s1)));
  Value *v2=new Variable;
  v2->SetName((s2));
  MathOperation *m=new NVMathOperation;
  m->Set(v1, o, v2);
  return m;
}

MathOperation *NewNCMath(const string &s1, const string &s2, const string &o)
{
  Value *v1=new Numeric;
  v1->SetValue((stod(s1)));
  Value *v2=new Constant;
  v2->SetName((s2));
  MathOperation *m=new NCMathOperation;
  m->Set(v1, o, v2);
  return m;
}

MathOperation *NewCVMath(const string &s1, const string &s2, const string &o)
{
  Value *v1=new Constant;
  v1->SetName(s1);
  Value *v2=new Variable;
  v2->SetName(s2);
  MathOperation *m=new CVMathOperation;
  m->Set(v1, o, v2);
  return m;
}

MathOperation *NewMVMath(const string &s1, const string &s2, const string &o, MathOperations &op)
{
  Value *v2=new Variable;
  v2->SetName(s2);
  MathOperation *m=new MVMathOperation;
  m->SetV2(v2);
  const unsigned int i=stoi(s1.substr(1, s1.size()));
  MathOperation *m1=op[i];

  if(m1->result!=NAN)
    {
      cout<<"m1->result!=NAN"<<'\n';
      Value *v1=new Numeric;
      v1->SetValue(m1->result);
      m->Set(v1, o, v2);
    }
  else
    {
      cout<<"NOT m1->result!=NAN"<<'\n';
    }
  return m;
}

MathOperation *NewCMMath(const string &s1, const string &s2, const string &o, MathOperations &op)
{
  Value *v1=new Constant;
  v1->SetName(s1);
  MathOperation *m=new CMMathOperation;
  m->SetV1(v1);
  const unsigned int i=stoi(s2.substr(1, s2.size()));
  MathOperation *m1=op[i];

  if(m1->result!=NAN)
    {
      cout<<"m->result!=NAN"<<'\n';
      Value *v2=new Numeric;
      v2->SetValue(m1->result);
      m->Set(v1, o, v2);
    }
  else
    {
      cout<<"NOT m1->result!=NAN"<<'\n';
    }
  return m;
}

MathOperation *Val(const vector<string> &equation, const unsigned int i, const Data &data, MathOperations &op, unsigned int &k)
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
  cout<<"Math operation "<<op.size()<<'\n';
  cout<<"   "<<"v"<<" "<<"c"<<" "<<"n"<<" "<<"m"<<'\n';
  cout<<"s1 "<<s1_variable<<" "<<s1_constant<<" "<<s1_numeric<<" "<<s1_math<<'\n';
  cout<<"s2 "<<s2_variable<<" "<<s2_constant<<" "<<s2_numeric<<" "<<s2_math<<'\n';

  if(s1_variable and s2_variable)
    {
      cout<<"s1_variable and s2_variable"<<'\n';
      Value *v1=new Variable;
      v1->SetName(s1);
      Value *v2=new Variable;
      v2->SetName(s2);
      MathOperation *m=new VVMathOperation;
      m->Set(v1, o, v2);
      return m;
    }
  if(s1_variable and s2_constant)
      {
	cout<<"s1_variable and s2_constant"<<'\n';
	return NewCVMath(s2, s1, o);
    }
  else if(s1_variable and s2_numeric)
    {
      cout<<"s1_variable and s2_numeric "<<s2<<'\n';
      return NewNVMath(s2, s1, o);
    }
  else if(s1_variable and s2_math)
    {
      cout<<"s1_variable and s2_math"<<'\n';
      return NewMVMath(s2, s1, o, op);
    }
  else if(s1_constant and s2_variable)
    {
      cout<<"s1_constant and s2_variable"<<'\n';
      return NewCVMath(s1, s2, o);
    }
  else if(s1_constant and s2_constant)
      {
      cout<<"s1_constant and s2_constant"<<'\n';
      Value *v1=new Constant;
      v1->SetName(s1);
      Value *v2=new Constant;
      v2->SetName(s2);
      MathOperation *m=new CCMathOperation;
      m->Set(v1, o, v2);
      return m;
    }
  else if(s1_constant and s2_numeric)
    {
      cout<<"s1_constant and s2_numeric "<<s2<<'\n';
      return NewNCMath(s2, s1, o);
    }
  else if(s1_constant and s2_math)
    {
      cout<<"s1_constant and s2_math"<<'\n';
      return NewCMMath(s1, s2, o, op);
    }
  else if(s1_numeric and s2_variable)
    {
      cout<<"s1_numeric and s2_varible"<<'\n';
      return NewNVMath(s1, s2, o);
    }
   else if(s1_numeric and s2_constant)
    {
      cout<<"s1_numeric and s2_constant"<<'\n';
      return NewNCMath(s1, s2, o);
    }
  else if(s1_numeric and s2_numeric)
    {
      cout<<"s1_numeric and s2_numeric"<<'\n';
      Value *v1=new Numeric;
      v1->SetValue(stod(s1));
      Value *v2=new Numeric;
      v2->SetValue(stod(s2));
      MathOperation *m=new NNMathOperation;
      m->SetV1(v1);
      m->SetV2(v2);
      m->SetOperator(o);
      m->Calculate();
      return m;
    }
   else if(s1_numeric and s2_math)
     {
       cout<<"s1_numeric and s2_math"<<'\n';
       return NewNMMath(s1, s2, o, op);
     }
  else if(s1_math and s2_variable)
    {
      cout<<"s1_math and s2_variable"<<'\n';
      return NewMVMath(s1, s2, o, op);
    }
  else if(s1_math and s2_constant)
      {
      cout<<"s1_math and s2_constant"<<'\n';
      return NewCMMath(s2, s1, o, op);
    }
  else if(s1_math and s2_numeric)
    {
      cout<<"s1_math and s2_numeric"<<'\n';
      return NewNMMath(s2, s1, o, op);
    }
  else if(s1_math and s2_math)
    {
      cout<<"s1_math and s2_math "<<s1<<" "<<s2<<'\n';
      MathOperation *m=new MMMathOperation;
      const unsigned int i=stoi(s1.substr(1, s1.size()));
      const unsigned int j=stoi(s2.substr(1, s2.size()));
      MathOperation *m1=op[i];
      MathOperation *m2=op[j];

      if(m1->result!=NAN and m2->result!=NAN)
	{
	  cout<<"m1->result!=NAN and m2->result!=NAN"<<'\n';
	  Value *v1=new Numeric;
	  v1->SetValue(m1->result);
	  Value *v2=new Numeric;
	  v2->SetValue(m2->result);
	  m->Set(v1, o, v2);
	  m->Calculate();
	}
      else
	{
	  cout<<"NOT m1->result!=NAN and m2->result!=NAN"<<'\n';
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

vector<string> FindOperator(vector<string> equation, const string &find, unsigned int &k, MathOperations &ooo, const Data &data)
{
  unsigned int i=0;

  while(i<equation.size())
    {
      if(find==equation[i])
	{
	  ooo.emplace_back(Val(equation, i, data, ooo, k));
	  cout<<"Adding "<<"@"+to_string(k)<<"="<<equation[i-1]<<equation[i]<<equation[i+1]<<" "<<ooo.size()<<'\n';
	  equation[i]="@"+to_string(k);
	  equation.erase(equation.begin()+i+1);
	  equation.erase(equation.begin()+i-1);
	  cout<<"k="<<k<<" size "<<ooo.size()<<'\n';
	  k++;

	  i=0;
	  cout<<" "<<'\n';
	  continue;
	}
      i++;
    }
  return equation;
}

void GetOrder(vector<string> &equation, unsigned int &k, MathOperations &ooo, const Data &data)
{
  for(const auto&i: OPERATORS) equation=FindOperator(equation, i, k, ooo, data);
}

vector<string> RemoveOpenClose(vector<string> equation)
{
  // Removes unnecessary parenthesis from equations such as ((1+(a+b)))
  const unsigned int open=distance(equation.begin(), find(equation.begin(), equation.end(), OPEN));
  const unsigned int close=distance(equation.begin(), find(equation.begin(), equation.end(), CLOSE));
  if(open!=equation.size() and close!=equation.size()) equation=Remove(equation, open, close);
  return equation;
}

vector<string> GetParenthesis(const vector<string> &equation, const int &open, const int &close, unsigned int &k, MathOperations &ooo, const Data &data)
{
  vector<string> v1{equation.begin()+open+1, equation.begin()+close};
  GetOrder(v1, k, ooo, data);
  v1=test(v1, k, ooo, data);
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

Map<string, MathOperations> ParseEquations(const SMap &equations_map, const Data &data)
{
    // Set calculation order of  an equation according to order of operations:

    // 1. Parentheses
    // 2. Exponents
    // 3. Multiplication and division
    // 4. Addition and subtraction

  vector<string> v;
  unsigned int k=0;
  MathOperations op;
  Map<string, MathOperations> equations_map2;
  equations_map2.reserve(equations_map.size());

  for(const auto& [name, equation]: equations_map)
    {
      v=ToVector(equation);
      v=RemoveOpenClose(v);
      cout<<"EQUATION"<<'\n';
      print_vector2(v);
      v=test(v, k, op, data);
      GetOrder(v, k, op, data);
      equations_map2[name]=op;
      cout<<"size "<<op.size()<<'\n';
      k=0;
      op.clear();
      cout<<" "<<'\n';
    }
  // for(auto i: op)
  //   {
  //     delete i;
  //     // free(i);
  //   }
  // op.clear();
  return equations_map2;
}
