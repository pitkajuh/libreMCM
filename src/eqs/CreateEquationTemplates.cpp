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
#include <iostream>
#include <stdexcept>

using std::cout;
using MathOperations=vector<OpTmp>;

Value* ValueCheck(const string &s, const vector<string> diagonal, const unordered_map<string, string> &constants_map)
{
  const bool is_variable=IsIn(s, diagonal);
  const bool is_constant=IsIn(s, constants_map);
  const bool is_numerical=IsNumerical(s);

  if(is_variable)
    {
      Value *v=new Variable(s);
      return v;
    }
  else if(is_constant)
    {
      Value *v=new Constant(s);
      return v;
    }
  else if(is_numerical)
    {
      cout<<"num "<<s<<'\n';
      Value *v=new Value(s);
      return v;
    }
  else
    {
       throw std::invalid_argument("Value "+s+" is not a constant, variable or numerical value.");
    }
}

MathOperation GetValue(const vector<OpTmp> &v, const vector<string> diagonal, const unordered_map<string, string> &constants_map)
{
  Value *v1;
  Value *v2;
  MathOperation op;

  for(const auto &i: v)
    {
      v1=ValueCheck(i.value1, diagonal, constants_map);
      v2=ValueCheck(i.value2, diagonal, constants_map);
      op.v1=v1;
      op.v2=v2;
      delete v1;
      delete v2;
    }
  return op;
}

void CreateEquationTemplates(const unordered_map<string, MathOperations> &equations_map, const Csv &csv, const unordered_map<string, string> &constants_map)
{
  const vector<string> diagonal=csv.diagonal;
  MathOperation op;
  // Value *v1=new Value;

  for(const auto &[key, value]: equations_map)
    {
      // v1=GetValue(value, diagonal, constants_map);
      op=GetValue(value, diagonal, constants_map);
    }
  // delete v1;
  // cout<<"aoe "<<IsIn("void", diagonal)<<" "<<IsIn("void", constants_map)<<'\n';
  cout<<"aoe "<<IsIn("a", constants_map)<<'\n';
}
