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

// Value *ValueCheck(const string &s, const Data &data, MathOperations &op, const int i)
// {
//   const bool is_variable=IsIn(s, data.diagonal);
//   const bool is_constant=IsIn(s, data.constants_map);
//   const bool is_numerical=IsNumerical(s);

//   if(is_variable)
//     {
//       // No value will be set yet. Depend on the initial values.
//       Value *v=new Variable;
//       v->SetName(s);
//       return v;
//     }
//   else if(is_constant)
//     {
//       // No value will be set yet. Value will change in probabilistic simulation.
//       Value *v=new Constant;
//       v->SetName(s);
//       return v;
//     }
//   else if(is_numerical)
//     {
//       // No name will be set, only value such as 1,2,3 etc.
//       Value *v=new Numeric;
//       v->SetValue(std::stod(s));
//       return v;
//     }
//   else if(i-1<op.size())
//     {
//       // Is a math operation.
//       const unsigned int i=std::stoi(s.substr(1, s.size()));
//       cout<<"is math "<<i<<" "<<op.size()<<" "<<'\n';
//       // MathOperation *op=op[i];
//       Value *v=new MathOperationValue;
//       return v;
//     }
//   else throw std::invalid_argument("Value "+s+" is not a constant, variable/compartment or numerical value.");
// }

void Val(const vector<string> &equation, const unsigned int i, const Data &data, MathOperations &op, const unsigned int k)
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

  if(s1_variable and s2_variable)
    {
      cout<<"s1_variable and s2_variable"<<'\n';
      Value *v1=new Variable;
      v1->SetName(s1);
      Value *v2=new Variable;
      v2->SetName(s2);
      // MathOperation *m=new NumericMathOperation;
      // delete m;
      delete v1;
      delete v2;
    }
  else if(s1_variable and s2_constant)
      {
      cout<<"s1_variable and s2_constant"<<'\n';
      Value *v1=new Constant;
      v1->SetName(s2);
      Value *v2=new Variable;
      v2->SetName(s1);
      delete v1;
      delete v2;
    }
  else if(s1_variable and s2_numeric)
    {
      cout<<"s1_variable and s2_numeric "<<s2<<'\n';
      Value *v1=new Numeric;
      v1->SetValue(stod(s2));
      Value *v2=new Variable;
      v2->SetName(s1);
      delete v1;
      delete v2;
    }
    else if(s1_variable and s2_math)
    {
      cout<<"s1_variable and s2_math"<<'\n';
      Value *v1=new MathOperationValue;
      v1->SetName(s2);
      Value *v2=new Variable;
      v2->SetName(s1);
      delete v1;
      delete v2;
    }
  else if(s1_constant and s2_variable)
    {
      cout<<"s1_constant and s2_variable"<<'\n';
      Value *v1=new Constant;
      v1->SetName(s1);
      Value *v2=new Variable;
      v2->SetName(s2);
      delete v1;
      delete v2;
    }
  else if(s1_constant and s2_constant)
      {
      cout<<"s1_constant and s2_constant"<<'\n';
      Value *v1=new Constant;
      v1->SetName(s1);
      Value *v2=new Constant;
      v2->SetName(s2);
      delete v1;
      delete v2;
    }
  else if(s1_constant and s2_numeric)
    {
      cout<<"s1_constant and s2_numeric "<<s2<<'\n';
      Value *v1=new Numeric;
      v1->SetValue(stod(s2));
      Value *v2=new Constant;
      v2->SetName(s1);
      delete v1;
      delete v2;
    }
  else if(s1_constant and s2_math)
    {
      cout<<"s1_constant and s2_math"<<'\n';
      Value *v1=new Constant;
      v1->SetName(s1);
      Value *v2=new MathOperationValue;
      v2->SetName(s2);
      delete v1;
      delete v2;
    }
  else if(s1_numeric and s2_variable)
    {
      cout<<"s1_numeric and s2_varible"<<'\n';
      Value *v1=new Numeric;
      v1->SetValue(stod(s1));
      Value *v2=new Variable;
      v2->SetName(s2);
      MathOperation *m=new NumericMathOperation;
      delete m;
      delete v1;
      delete v2;
    }
   else if(s1_numeric and s2_constant)
    {
      cout<<"s1_numeric and s2_constant"<<'\n';
      Value *v1=new Numeric;
      v1->SetValue(stod(s1));
      Value *v2=new Constant;
      v1->SetName(s2);
      MathOperation *m=new NumericMathOperation;
      delete m;
      delete v1;
      delete v2;
    }
   else if(s1_numeric and s2_numeric)
    {
      cout<<"s1_numeric and s2_numeric "<<s1<<" "<<s2<<'\n';
      Value *v1=new Numeric;
      v1->SetValue(stod(s1));
      Value *v2=new Numeric;
      v2->SetValue(stod(s2));
      MathOperation *m=new NumericMathOperation;
      delete m;
      delete v1;
      delete v2;
    }
   else if(s1_numeric and s2_math)
    {
      cout<<"s1_numeric and s2_math "<<s1<<'\n';
      Value *v1=new Numeric;
      v1->SetValue(stod(s1));
      Value *v2=new MathOperationValue;
      v2->SetName(s2);
      MathOperation *m=new NumericMathOperation;
      delete m;
      delete v1;
      delete v2;
    }
  else if(s1_math and s2_variable)
    {
      cout<<"s1_math and s2_variable"<<'\n';
      Value *v1=new MathOperationValue;
      v1->SetName(s1);
      Value *v2=new Variable;
      v2->SetName(s2);
      delete v1;
      delete v2;
    }
  else if(s1_math and s2_constant)
      {
      cout<<"s1_math and s2_constant"<<'\n';
      Value *v1=new MathOperationValue;
      v1->SetName(s1);
      Value *v2=new Constant;
      v2->SetName(s2);
      delete v1;
      delete v2;
    }
  else if(s1_math and s2_numeric)
    {
      cout<<"s1_math and s2_numeric "<<s2<<'\n';
      Value *v1=new Numeric;
      v1->SetValue(stod(s2));
      Value *v2=new MathOperationValue;
      v2->SetName(s1);
      delete v1;
      delete v2;
    }
  else if(s1_math and s2_math)
    {
      cout<<"s1_math and s2_math"<<'\n';
      Value *v1=new MathOperationValue;
      v1->SetName(s1);
      Value *v2=new MathOperationValue;
      v2->SetName(s2);
      delete v1;
      delete v2;
    }
  else if(!s1_variable && !s1_constant && !s1_numeric && !s1_math)
    {
      throw std::invalid_argument("Value "+s1+" is not a constant, variable/compartment or numeric value.");
    }
  else
    {
      throw std::invalid_argument("Value "+s2+" is not a constant, variable/compartment or numeric value.");
    }
}

vector<string> FindOperator(vector<string> equation, const string &find, unsigned int &k, MathOperations &ooo, const Data &data)
{
  unsigned int i=0;
  // MathOperation operation;
  Value *v1;
  Value *v2;

  while(i<equation.size())
    {
      if(find==equation[i])
	{
	  // operation->SetMathOp(equation[i]);
	  // v1=ValueCheck(equation[i-1], data, ooo, k);
	  // v2=ValueCheck(equation[i+1], data, ooo, k);
	  // operation->SetValues(v1, v2);
	  // ooo.emplace_back(operation);
	  Val(equation, i, data, ooo, k);
	  // ooo["@"+to_string(k)]=operation;
	  cout<<"Adding "<<"@"+to_string(k)<<"="<<equation[i-1]<<equation[i]<<equation[i+1]<<" "<<ooo.size()<<'\n';
	  equation[i]="@"+to_string(k);
	  equation.erase(equation.begin()+i+1);
	  equation.erase(equation.begin()+i-1);
	  k++;
	  i=0;
	  // delete operation;
	  // delete v1;
	  // delete v2;
	  continue;
	}
      i++;
    }
  // cout<<"end"<<'\n';
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
      cout<<" EQUATION"<<'\n';
      print_vector2(v);
      v=test(v, k, op, data);
      GetOrder(v, k, op, data);
      equations_map2[name]=op;
      k=0;
      op.clear();
      cout<<" "<<'\n';
    }
  return equations_map2;
}
