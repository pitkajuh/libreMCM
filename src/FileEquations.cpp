#include <string_view>
#include "FileEquations.h"
#include "FileGraph.h"
#include "Equation.h"

using std::to_string;
using std::string_view;

constexpr string_view OPEN="(";
constexpr string_view CLOSE=")";
constexpr string_view OPERATORS2[7]={"^", "/", "*", "+", "-", OPEN, CLOSE};
constexpr string_view OPERATORS[5]={"^", "/", "*", "+", "-"};
constexpr double notSet=std::numeric_limits<double>::quiet_NaN();

uint8_t FileEquations::GetOpen(const string &str, const uint8_t close)
{
  // Find the index of the innermost open parenthesis (.
  // Variable uint8_t close is the index for the corresponding closing
  // parenthesis
  uint8_t open=str.find(OPEN);
  uint8_t openPrevious=open;

  while(open<close)
    {
      open=str.find(OPEN, open+1);

      if(open>close)
	{
	  open=openPrevious;
	  break;
	}
      openPrevious=open;
    }

  return open;
}

void FileEquations::RemoveOpenClose(string &equation, uint8_t &id, vector<TestStr> &a)
{
  // Find math operations inside parenthesis ( and ).
  uint8_t close=equation.find(CLOSE);
  uint8_t open=GetOpen(equation, close);

  while(open<equation.size())
    {
      open=GetOpen(equation, close);

      if(open>equation.size()) break;

      string sub1=equation.substr(open+1, close-open-1);
      GetOrder(sub1, id, a);

      // String "@"+to_string(id-1) is a placeholder variable.
      equation.replace(equation.begin()+open, equation.begin()+close+1, "@"+to_string(id-1));

      close=equation.find(CLOSE);
    }
}

void FileEquations::RemoveMathOperation(const uint8_t id, std::set<uint8_t> &removeIndices, std::unordered_set<double*> &removeAddress, const MathOperation &v, const MathOperation &v0)
{
  if(v.value1!=v0.value1)
    {
      removeIndices.insert(id);
      removeAddress.insert(v.value1);
    }

  if(v.value2!=v0.value2)
    {
      removeIndices.insert(id);
      removeAddress.insert(v.value2);
    }
}

void FileEquations::CreateMathOperation(const string &s1, const string &s2, const char mathOperator, const Bools &b1, const Bools &b2, MathOperators &operators, vector<MathOperation> &vv, vector<double> &variableValue, const vector<uint16_t> &noOfInitialValue, Graph &graph, std::set<uint8_t> &removeIndices, std::unordered_set<double*> &removeAddress)
{
  MathOperation v0;

  if(b1.variable and b2.variable)
    {
      v0.result=new double(notSet);
      v0.mathOperator=operators.GetOperator(mathOperator);
      v0.value1Negative=b1.negative;
      v0.value2Negative=b2.negative;

      const uint8_t id1=graph.GetVertex((b1.negative)?s1.substr(1):s1).GetId();
      const uint8_t from1=(id1==0)?0:noOfInitialValue[id1-1];
      const uint8_t to1=noOfInitialValue[id1];

      const uint8_t id2=graph.GetVertex((b2.negative)?s2.substr(1):s2).GetId();
      const uint8_t from2=(id2==0)?0:noOfInitialValue[id2-1];
      const uint8_t to2=noOfInitialValue[id2];

      if(to1-from1!=to2-from2) cout<<"Warning, different number of initial values."<<'\n';

      // Multiply by -1 if b1.negative=1 and b2.negative=1?
      v0.value1=&variableValue[from1];
      v0.value2=&variableValue[from2];
    }
  else if(b1.variable and b2.constant)
    {
      v0.result=new double(notSet);
      v0.value1Negative=b1.negative;

      const uint8_t id1=graph.GetVertex((b1.negative)?s1.substr(1):s1).GetId();
      const uint8_t from1=(id1==0)?0:noOfInitialValue[id1-1];
      v0.value1=&variableValue[from1];

      if(b1.negative)
	{
	  throw std::invalid_argument("b1.negative is true, i don't know what to do.");
	}
      if(b2.negative)
	{
	  v0.value2Negative=-1;
	  v0.value2=new double(constants[constantNames[s2.substr(1)]]);
	}
      else v0.value2=new double(constants[constantNames[s2]]);

      v0.mathOperator=operators.GetOperator(mathOperator);
    }
  else if(b1.variable and b2.numeric)
    {
      v0.result=new double(notSet);
      v0.value1Negative=b1.negative;

      const uint8_t id1=graph.GetVertex((b1.negative)?s1.substr(1):s1).GetId();
      const uint8_t from1=(id1==0)?0:noOfInitialValue[id1-1];
      v0.value1=&variableValue[from1];
      v0.value2=new double(stod(s2));
      v0.mathOperator=operators.GetOperator(mathOperator);
    }
  else if(b1.constant and b2.variable)
    {
      v0.value2Negative=b2.negative;
      const uint8_t id2=graph.GetVertex((b2.negative)?s2.substr(1):s2).GetId();
      v0.value2=&variableValue[id2];
      v0.result=new double(notSet);
      v0.mathOperator=operators.GetOperator(mathOperator);

      if(b1.negative)
	{
	  v0.value1Negative=-1;
	  v0.value1=new double(constants[constantNames[s1.substr(1)]]);
	}
      else v0.value1=new double(constants[constantNames[s1]]);
    }
  else if(b1.constant and b2.constant)
    {
      v0.result=new double(notSet);

      if(b1.negative)
	{
	  v0.value1Negative=-1;
	  v0.value1=new double(constants[constantNames[s1.substr(1)]]);
	}
      else v0.value1=new double(constants[constantNames[s1]]);

      if(b2.negative)
	{
	  v0.value2Negative=-1;
	  v0.value2=new double(constants[constantNames[s2.substr(1)]]);
	}
      else v0.value2=new double(constants[constantNames[s2]]);

      v0.mathOperator=operators.GetOperator(mathOperator);
    }
  else if(b1.constant and b2.numeric)
    {
      v0.result=new double(notSet);
      if(b1.negative)
	{
	  v0.value1Negative=-1;
	  v0.value1=new double(constants[constantNames[s1.substr(1)]]);
	}
      else v0.value1=new double(constants[constantNames[s1]]);
      v0.value2=new double(stod(s2));
      v0.mathOperator=operators.GetOperator(mathOperator);
    }
  else if(b1.numeric and b2.variable)
    {
      v0.result=new double(notSet);
      v0.value1=new double(stod(s1));
      v0.value2Negative=b2.negative;
      const uint8_t id2=graph.GetVertex((b2.negative)?s2.substr(1):s2).GetId();
      const uint8_t from2=(id2==0)?0:noOfInitialValue[id2-1];
      v0.value2=&variableValue[from2];
      v0.mathOperator=operators.GetOperator(mathOperator);
    }
  else if(b1.numeric and b2.constant)
    {
      v0.result=new double(notSet);
      v0.value1=new double(stod(s1));

      if(b2.negative)
	{
	  v0.value2Negative=-1;
	  v0.value2=new double(constants[constantNames[s2.substr(1)]]);
	}
      else v0.value2=new double(constants[constantNames[s2]]);
      v0.mathOperator=operators.GetOperator(mathOperator);
    }
  else if(b1.numeric and b2.numeric)
    {
      v0.result=new double(operators.GetOperator(mathOperator)->Calculate(stod(s1), stod(s2)));
    }
  else if(b1.math and b2.math)
    {
      const uint8_t id1=stoi(s1.substr(1));
      const uint8_t id2=stoi(s2.substr(1));
      const MathOperation v1=vv[id1];
      const MathOperation v2=vv[id2];

      if(!std::isnan(*v1.result) and !std::isnan(*v2.result))
	{
	  v0.mathOperator=operators.GetOperator(mathOperator);
	  v0.value2=v2.result;
	  v0.value1=v1.result;
	  v0.result=new double(notSet);
	  v0.Calculate();

	  RemoveMathOperation(id1, removeIndices, removeAddress, v1, v0);
	  RemoveMathOperation(id2, removeIndices, removeAddress, v2, v0);
	}
      else if(!std::isnan(*v1.result))
	{
	  v0.result=new double(notSet);
	  v0.mathOperator=operators.GetOperator(mathOperator);
	  v0.value1=v1.result;
	  v0.value2=v2.result;
	  RemoveMathOperation(id1, removeIndices, removeAddress, v1, v0);
	}
      else if(!std::isnan(*v2.result))
	{
	  v0.result=new double(notSet);
	  v0.mathOperator=operators.GetOperator(mathOperator);
	  v0.value1=v1.result;
	  v0.value2=v2.result;
	  RemoveMathOperation(id2, removeIndices, removeAddress, v2, v0);
	}
      else
	{
	  v0.result=new double(notSet);
	  v0.mathOperator=operators.GetOperator(mathOperator);
	  v0.value1=v1.result;
	  v0.value2=v2.result;
	}
    }
  else if(b1.math and b2.constant)
    {
      v0.mathOperator=operators.GetOperator(mathOperator);
      v0.result=new double(notSet);

      if(b2.negative)
	{
	  v0.value2Negative=-1;
	  v0.value2=new double(constants[constantNames[s2.substr(1)]]);
	}
      else v0.value2=new double(constants[constantNames[s2]]);
      const uint8_t id1=stoi(s1.substr(1));
      const MathOperation v1=vv[id1];

      if(!std::isnan(*v1.result)) RemoveMathOperation(id1, removeIndices, removeAddress, v1, v0);
      v0.value1=v1.result;
    }
  else if(b1.math and b2.variable)
    {
      v0.result=new double(notSet);
      v0.value2Negative=b2.negative;
      const uint8_t id2=graph.GetVertex((b2.negative)?s2.substr(1):s2).GetId();
      v0.value2=&variableValue[id2];
      v0.mathOperator=operators.GetOperator(mathOperator);
      const uint8_t id1=stoi(s1.substr(1));
      const MathOperation v1=vv[id1];

      if(!std::isnan(*v1.result)) RemoveMathOperation(id1, removeIndices, removeAddress, v1, v0);
      v0.value1=v1.result;
    }
  else if(b1.numeric and b2.math)
    {
      const uint8_t id2=stoi(s2.substr(1));
      const MathOperation v2=vv[id2];

      if(!std::isnan(*v2.result))
	{
	  v0.mathOperator=operators.GetOperator(mathOperator);
	  v0.value2=v2.result;
	  v0.value1=new double(stod(s1));
	  v0.result=new double(notSet);
	  v0.Calculate();
	  RemoveMathOperation(id2, removeIndices, removeAddress, v2,  v0);
	}
      else
	{
	  v0.mathOperator=operators.GetOperator(mathOperator);
	  v0.result=new double(notSet);
	  v0.value1=new double(stod(s1));
	  v0.value2=v2.result;
	}
    }
  else if(b2.math and b1.constant)
    {
      v0.result=new double(notSet);
      v0.mathOperator=operators.GetOperator(mathOperator);
      const uint8_t id2=stoi(s2.substr(1));
      const MathOperation v2=vv[id2];

      if(b1.negative)
	{
	  v0.value1Negative=-1;
	  v0.value1=new double(constants[constantNames[s1.substr(1)]]);
	}
      else v0.value1=new double(constants[constantNames[s1]]);

      if(!std::isnan(*v2.result)) RemoveMathOperation(id2, removeIndices, removeAddress, v2,  v0);
      v0.value2=v2.result;
    }
  else if(b2.math and b1.variable)
    {
      const uint8_t id2=stoi(s2.substr(1));
      const MathOperation v2=vv[id2];
      const uint8_t id1=graph.GetVertex((b1.negative)?s1.substr(1):s1).GetId();
      const uint8_t from1=(id1==0)?0:noOfInitialValue[id1-1];

      v0.result=new double(notSet);
      v0.mathOperator=operators.GetOperator(mathOperator);

      v0.value1Negative=b1.negative;

      v0.value1=&variableValue[from1];
      if(!std::isnan(*v2.result)) RemoveMathOperation(id2, removeIndices, removeAddress, v2,  v0);
      v0.value2=v2.result;
    }
  else if(b2.numeric and b1.math)
    {
      const uint8_t id1=stoi(s1.substr(1));
      const MathOperation v1=vv[id1];

      if(!std::isnan(*v1.result))
	{
	  v0.mathOperator=operators.GetOperator(mathOperator);
	  v0.value1=v1.result;
	  v0.value2=new double(stod(s2));
	  v0.result=new double(notSet);
	  RemoveMathOperation(id1, removeIndices, removeAddress, v1, v0);
	}
      else
	{
	  v0.mathOperator=operators.GetOperator(mathOperator);
	  v0.value1=v1.result;
	  v0.value2=new double(stod(s2));
	  v0.result=new double(notSet);
	}
    }
  else if(!b1.variable and !b1.constant and !b1.numeric and !b1.math)
    {
      throw std::invalid_argument("Value \""+s1+"\" is not a constant, variable or numeric value.");
    }
  else
    {
      throw std::invalid_argument("Value \""+s2+"\" is not a constant, variable or numeric value.");
    }
  vv.emplace_back(v0);
}

Equations FileEquations::ParseEquations(Graph &graph, MathOperators &operators, vector<double> &variableValue, const vector<uint16_t> &noOfInitialValue)
{
  // Set calculation order of an equation according to order of operations:

  // 1. Parentheses
  // 2. Exponents
  // 3. Multiplication and division
  // 4. Addition and subtraction

  Equations equationsNew;

  for(auto& [id, v]: equations)
    {
      const vector<TestStr> equation=ToVector(v);
      std::set<uint8_t> removeIndices;
      std::unordered_set<double*> removeAddress;
      Equation equationNew;
      equationNew.id=id;

      for(const TestStr &eq: equation)
	{
	  const Bools b1(eq.str1, graph, constantNames);
	  const Bools b2(eq.str2, graph, constantNames);
	  CreateMathOperation(eq.str1, eq.str2, eq.op, b1, b2, operators, equationNew.vertices, variableValue, noOfInitialValue, graph, removeIndices, removeAddress);
	}

      uint8_t j=0;

      for(const auto &i: removeIndices)
	{
	  equationNew.vertices.erase(equationNew.vertices.begin()+i-j);
	  j++;
	}

      equationNew.size1=equationNew.vertices.size();

      for(const auto &i: removeAddress)
	{
	  delete i;
	}

      removeAddress.clear();
      removeIndices.clear();

      equationNew.vertices.reserve(equationNew.vertices.size());
      equationsNew.equations.emplace_back(equationNew);
    }
  equationsNew.equations.reserve(equationsNew.equations.size());
  equations.clear();
  return equationsNew;
}

void FileEquations::Convert(const map<uint16_t, string> &map)
{
  for(const auto &[key, value]: map)
    {
      constants[key]=std::stod(value);
    }
}

streampos FileEquations::SA(ifstream &file, streampos from, const string &line)
{
  pair<streampos, vector<string>> result;
  const string constants1="constants";
  const string equations1="equations";
  const string sub=line.substr(0, 9);

  if(sub==constants1)
    {
      result=ReadContent(file, from, constants1, 9);
      Convert(GetSettings(result.second, constantNames));
    }
  else if(sub==equations1)
    {
      result=ReadContent(file, from, equations1, 9);
      equations=GetSettings(result.second, equationNames);
    }
  from=result.first;
  return from;
}

uint8_t FileEquations::GetRight(const string &eq)
{
  uint8_t smallest=eq.size();
  const uint8_t size=smallest;

  for(const auto &i: OPERATORS2)
    {
      const uint8_t a=eq.find(i);

      if(a<size and a<smallest) smallest=a;
    }
  return smallest;
}

uint8_t FileEquations::GetLeft(string &str)
{
  uint8_t largest=0;
  uint8_t j=0;

  while(j<7)
    {
      for(const auto &i: OPERATORS2)
	{
	  const uint8_t a=str.find(i);

	  if(a>largest and a<str.size()) largest=a;
	  else j++;
	}
      if(j==7) break;

      str.erase(str.begin(), str.begin()+largest+1);
      largest=0;
      j=0;
    }
  return largest;
}

void FileEquations::GetOrder(string &str, uint8_t &id, vector<TestStr> &a)
{
  uint8_t at=0;

  while(str.size()>2)
    {
      uint8_t j=0;
      for(const auto &i: OPERATORS)
	{
	  at=str.find(i);
	  if(at<str.size()) break;
	  else j++;
	}
      // If j is equal to the total number of math operators after
      // looping through them, the string has no math operators.
      if(j==5) break;
      j=0;
      // Split the string into two parts around index "at" (left side
      // and right side).
      // For example str[at]="+", LHS="10" and RHS="3", then the string
      // is "10+x".

      // Get left hand side.
      string LHS=str.substr(0, at);
      const uint8_t size1=LHS.size();
      const uint8_t from1=GetLeft(LHS);
      LHS=LHS.substr(from1);

      // Get right hand side.
      string RHS=str.substr(at+1);
      const uint8_t to=GetRight(RHS);
      RHS=RHS.substr(0, to);
      const uint8_t size2=at+RHS.size()+1;
      const char a3{str[at]};
      const TestStr LHS1{LHS, a3, RHS};

      a.emplace_back(LHS1);

      str.replace(str.begin()+size1-LHS.size(), str.begin()+size2, "@"+to_string(id));
      id++;
    }
}

vector<TestStr> FileEquations::ToVector(string &eq)
{
  vector<string> equation;
  vector<TestStr> a;
  uint8_t id=0;

  RemoveOpenClose(eq, id, a);
  GetOrder(eq, id, a);
  a.reserve(id);

  if(a.size()==0)
    {
      a.reserve(1);
      const TestStr mo{eq, '+', "0"};
      a.emplace_back(mo);
    }
  return a;
}

FileEquations::FileEquations(const string &fileName)
{
  ReadFile(fileName);
}

void FileEquations::Read(const string &fileName)
{
  ReadFile(fileName);
}
