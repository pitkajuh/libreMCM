/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../util/IsIn.h"
#include "../types/MathOperation.h"
#include "../types/Csv.h"
#include "../inc/namespace.h"
#include <iostream>
#include <stdexcept>

using namespace libremcm;
using std::cout;
using MathOperations=Map<string, OpTmp>;

Value *ValueCheck(const string &s, const vector<string> &diagonal, SMap &constants_map, const MathOperations &v,  vector<MathOperation*> &ops)
{
  const bool is_variable=IsIn(s, diagonal);
  const bool is_constant=IsIn(s, constants_map);
  const bool is_math=IsIn(s, v);
  const bool is_numerical=IsNumerical(s);

  if(is_variable)
    {
      Value *v=new Variable;
      v->SetName(s);
      return v;
    }
  else if(is_constant)
    {
      Value *v=new Constant;
      v->SetName(s);
      return v;
    }
  else if(is_numerical)
    {
      // No name will be set, only value such as 1,2,3 etc.
      Value *v=new Numeric;
      v->SetValue(std::stod(s));
      return v;
    }
  else if(is_math)
    {
      const unsigned int i=std::stoi(s.substr(1, s.size()));
      cout<<"is math "<<i<<" "<<ops.size()<<" "<<'\n';
      MathOperation *op=ops[i];
      Value *v=new MathOperationValue;
      return v;
    }
  else throw std::invalid_argument("Value "+s+" is not a constant, variable/compartment or numerical value.");
}

MathOperation *GetValue(MathOperations v, const vector<string> &diagonal, SMap &constants_map)
{
  string s;
  Value *v1;
  Value *v2;
  MathOperation *op=new MathOperation;
  vector<MathOperation*> ops;

  for(unsigned int i=0; i<v.size(); i++)
    {
      s="@"+std::to_string(i);
      v1=ValueCheck(v[s].value1, diagonal, constants_map, v, ops);
      v2=ValueCheck(v[s].value2, diagonal, constants_map, v, ops);
      cout<<v.size()<<" "<<s<<" "<<v[s].value1<<v[s].math_operator<<v[s].value2<<'\n';
      cout<<" "<<'\n';
      op->v1=v1;
      op->SetMathOp(v[s].math_operator);
      op->v2=v2;
      // op->LinkMathOp();
      ops.emplace_back(op);
      delete v1;
      delete v2;
    }
  cout<<""<<'\n';
  return op;
}

void CreateEquationTemplates(const Map<string, MathOperations> &equations_map, const Csv &csv, SMap &constants_map)
{
  const vector<string> diagonal=csv.diagonal;
  MathOperation *op;

  for(const auto &[key, value]: equations_map)
    {
      cout<<key<<'\n';
      op=GetValue(value, diagonal, constants_map);
      delete op;
    }
}
