#include "FileEquations.h"
#include "FileGraph.h"
#include "Equation.h"

using std::to_string;

const string OPEN="(";
const string CLOSE=")";
const string OPERATORS2[7]={"^", "/", "*", "+", "-", OPEN, CLOSE};
const string OPERATORS[5]={"^", "/", "*", "+", "-"};

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
  cout<<"RemoveOpenClose "<<equation<<'\n';

  while(open<equation.size())
    {
      open=GetOpen(equation, close);

      if(open>equation.size()) break;

      string sub1=equation.substr(open+1, close-open-1);
      GetOrder(sub1, id, a);

      // String "@"+to_string(id-1) is a placeholder variable.
      equation.replace(equation.begin()+open, equation.begin()+close+1, "@"+to_string(id-1));

      cout<<equation<<" "<<sub1<<'\n';
      close=equation.find(CLOSE);
    }
  cout<<"+++++++++++"<<'\n';
}

Types FileEquations::GetTypes(const Bools &b)
{
  if(b.variable) return Types::variable;
  if(b.constant) return Types::constant;
  if(b.numeric) return Types::numeric;
  if(b.math) return Types::math;
  return Types::NotFound;
}

void FileEquations::CreateVertex(const string &s1, const string &s2, const string &mathOperator, const Bools &b1, const Bools &b2, MathOperators &operators, vector<VertexNew> &vv, double *variableValue, const vector<uint16_t> &noOfInitialValue, map<string, uint16_t> &data, vector<uint8_t> &removeIndices, std::unordered_set<double*> &removeAddress)
{
  cout<<"Create "<<s1<<mathOperator<<s2<<'\n';
  VertexNew v0;
  // VertexNew v1;
  // uint8_t id1;
  // uint8_t id2;

  // if(b1.variable)
  //   {
  //     v0.mathOperator=operators.GetOperator(mathOperator);
  //     v0.value1Negative=b1.negative;
  //     id1=data[(b1.negative)?s1.substr(1):s1];
  //     const uint16_t from1=(id1==0)?0:noOfInitialValue[id1-1];
  //     const uint16_t to1=noOfInitialValue[id1];
  //     v0.value1=&variableValue[from1];
  //   }
  // else if(b1.constant and b1.negative)
  //   {
  //     v0.value1Negative=1;
  //     v0.value1=new double(constants[constantNames[s1.substr(1)]]);
  //   }
  // else if(b1.constant) v0.value1=new double(constants[constantNames[s1]]);
  // else if(b1.numeric) v0.value1=new double(stod(s1));
  // else if(b1.math)
  //   {
  //     id1=stoi(s1.substr(1));
  //     v1=vv[id1];
  //     v0.value1=v1.result;
  //   }

  // if(b2.variable)
  //   {
  //     v0.value2Negative=b2.negative;
  //     id2=data[(b2.negative)?s2.substr(1):s2];
  //     const uint16_t from2=(id2==0)?0:noOfInitialValue[id2-1];
  //     const uint16_t to2=noOfInitialValue[id2];
  //     v0.value2=&variableValue[from2];
  //     if(v0.value1!=nullptr) cout<<"b2.variable v0.value1!=nullptr"<<'\n';
  //     if(v1.result!=nullptr) cout<<"b2.variable v1.result!=nullptr"<<'\n';
  //   }
  // else if(b2.constant and b2.negative)
  //   {
  //     v0.value2Negative=1;
  //     v0.value2=new double(constants[constantNames[s2.substr(1)]]);
  //     if(v0.value1!=nullptr) cout<<"b2.constant and neg v0.value1!=nullptr"<<'\n';
  //     if(v1.result!=nullptr) cout<<"b2.constant and neg v1.result!=nullptr"<<'\n';
  //   }
  // else if(b2.constant)
  //   {
  //     v0.value2=new double(constants[constantNames[s2]]);
  //     if(v0.value1!=nullptr) cout<<"b2.constant v0.value1!=nullptr"<<'\n';
  //     if(v1.result!=nullptr) cout<<"b2.constant v1.result!=nullptr"<<'\n';
  //   }
  // else if(b2.numeric)
  //   {
  //     v0.value2=new double(stod(s2));
  //     if(v0.value1!=nullptr) cout<<"b2.numeric v0.value1!=nullptr"<<'\n';
  //     if(v1.result!=nullptr) cout<<"b2.numeric v1.result!=nullptr"<<'\n';
  //   }
  // else if(b2.math)
  //   {
  //     id2=stoi(s2.substr(1));
  //     const VertexNew v2=vv[id2];

  //     if(v0.value1!=nullptr and v2.result!=nullptr)
  // 	{
  // 	  cout<<"v0.value1!=nullptr and v2.result!=nullptr"<<'\n';
  // 	  v0.result=new double(operators.GetOperator(mathOperator)->Calculate(*v0.value1, *v2.result));
  // 	  v0.value1=nullptr;

  // 	  const vector<double*> v11={v2.value1, v2.value2};
  // 	  const std::pair<uint8_t, vector<double*>> v01{id2, v11};
  // 	  remove.emplace_back(v01);

  // 	  const vector<double*> v21={v1.value1, v1.value2};
  // 	  const std::pair<uint8_t, vector<double*>> v02{id2, v21};
  // 	  remove.emplace_back(v02);
  // 	}
  //     else
  // 	{
  // 	  v0.mathOperator=operators.GetOperator(mathOperator);
  // 	  v0.value2=v2.result;
  // 	}
  //   }





  if(b1.variable and b2.variable)
    {
      // cout<<"b1.variable and b2.variable"<<'\n';
      v0.mathOperator=operators.GetOperator(mathOperator);
      v0.value1Negative=b1.negative;
      v0.value2Negative=b2.negative;

      const uint8_t id1=data[(b1.negative)?s1.substr(1):s1];
      const uint8_t from1=(id1==0)?0:noOfInitialValue[id1-1];
      const uint8_t to1=noOfInitialValue[id1];

      const uint8_t id2=data[(b2.negative)?s2.substr(1):s2];
      const uint8_t from2=(id2==0)?0:noOfInitialValue[id2-1];
      const uint8_t to2=noOfInitialValue[id2];

      if(to1-from1!=to2-from2) cout<<"Warning, different number of initial values."<<'\n';

      v0.value1=&variableValue[from1];
      v0.value2=&variableValue[from2];
      // cout<<"ok1"<<'\n';
    }
  else if(b1.variable and b2.constant)
    {
      // cout<<"b1.variable and b2 constant"<<'\n';
      v0.value1Negative=b1.negative;
      const uint8_t id1=data[(b1.negative)?s1.substr(1):s1];
      const uint8_t from1=(id1==0)?0:noOfInitialValue[id1-1];
      v0.value1=&variableValue[from1];

      if(b2.negative)
	{
	  v0.value2Negative=1;
	  v0.value2=new double(constants[constantNames[s2.substr(1)]]);
	}
      else v0.value2=new double(constants[constantNames[s2]]);

      v0.mathOperator=operators.GetOperator(mathOperator);
    }
  else if(b1.variable and b2.numeric)
    {
      // cout<<"b1.variable and b2 numeric"<<'\n';
      v0.value1Negative=b1.negative;
      const uint8_t id1=data[(b1.negative)?s1.substr(1):s1];
      // cout<<"ID "<<id1<<'\n';
      const uint8_t from1=(id1==0)?0:noOfInitialValue[id1-1];
      // cout<<"ID "<<id1<<'\n';
      v0.value1=&variableValue[from1];
      v0.value2=new double(stod(s2));
      v0.mathOperator=operators.GetOperator(mathOperator);
    }
  else if(b1.constant and b2.variable)
    {
      // cout<<"b1.constant and b2.variable"<<'\n';
      v0.value2Negative=b2.negative;
      const uint8_t id2=data[(b2.negative)?s2.substr(1):s2];
      const uint8_t from2=(id2==0)?0:noOfInitialValue[id2-1];
      v0.value2=&variableValue[from2];

      if(b1.negative)
	{
	  v0.value1Negative=1;
	  v0.value1=new double(constants[constantNames[s1.substr(1)]]);
	}
      else v0.value1=new double(constants[constantNames[s1]]);

      v0.mathOperator=operators.GetOperator(mathOperator);
    }
  else if(b1.constant and b2.constant)
    {
      // cout<<"b1.constant and b2.constant"<<'\n';
      if(b1.negative)
	{
	  v0.value1Negative=1;
	  v0.value1=new double(constants[constantNames[s1.substr(1)]]);
	}
      else v0.value1=new double(constants[constantNames[s1]]);

      if(b2.negative)
	{
	  v0.value2Negative=1;
	  v0.value2=new double(constants[constantNames[s2.substr(1)]]);
	}
      else v0.value2=new double(constants[constantNames[s2]]);

      v0.mathOperator=operators.GetOperator(mathOperator);
    }
  else if(b1.constant and b2.numeric)
    {
      // cout<<"b1.constant and b2.numeric"<<'\n';
      if(b1.negative)
	{
	  v0.value1Negative=1;
	  v0.value1=new double(constants[constantNames[s1.substr(1)]]);
	}
      else v0.value1=new double(constants[constantNames[s1]]);
      v0.value2=new double(stod(s2));
      v0.mathOperator=operators.GetOperator(mathOperator);
    }
  else if(b1.numeric and b2.variable)
    {
      // cout<<"b1.numeric and b2.variable"<<'\n';
      v0.value1=new double(stod(s1));
      v0.value2Negative=b2.negative;
      const uint8_t id2=data[(b2.negative)?s2.substr(1):s2];
      const uint8_t from2=(id2==0)?0:noOfInitialValue[id2-1];
      v0.value2=&variableValue[from2];
      v0.mathOperator=operators.GetOperator(mathOperator);
    }
  else if(b1.numeric and b2.constant)
    {
      // cout<<"b1.numeric and b2.constant "<<s1<<" "<<s2<<'\n';
      v0.value1=new double(stod(s1));

      if(b2.negative)
	{
	  v0.value2Negative=1;
	  v0.value2=new double(constants[constantNames[s2.substr(1)]]);
	}
      else v0.value2=new double(constants[constantNames[s2]]);
      v0.mathOperator=operators.GetOperator(mathOperator);
    }
  else if(b1.numeric and b2.numeric)
    {
      // cout<<"b1.numeric and b2.numeric "<<s1<<" "<<s2<<'\n';
      v0.result=new double(operators.GetOperator(mathOperator)->Calculate(stod(s1), stod(s2)));
    }
  else if(b1.math and b2.math)
    {
      // cout<<"b1.math and b2.math "<<'\n';
      const uint8_t id1=stoi(s1.substr(1));
      const uint8_t id2=stoi(s2.substr(1));
      const VertexNew v1=vv[id1];
      const VertexNew v2=vv[id2];

      if(v1.result!=nullptr and v2.result!=nullptr)
	{
	  cout<<"v1.result!=nullptr and v2.result!=nullptr"<<'\n';
	  v0.result=new double(operators.GetOperator(mathOperator)->Calculate(*v1.result, *v2.result));
	  // remove.emplace_back({id1});
	  // remove.emplace_back(id2);
	  removeIndices.emplace_back(id1);
	  removeIndices.emplace_back(id2);
	  removeAddress.insert(v1.value1);
	  removeAddress.insert(v1.value2);
	  removeAddress.insert(v1.result);
	  removeAddress.insert(v2.value1);
	  removeAddress.insert(v2.value2);
	  removeAddress.insert(v2.result);
	  cout<<v2.result<<" "<<v1.result<<'\n';
	}
      else
	{
	  v0.mathOperator=operators.GetOperator(mathOperator);
	  // cout<<"else "<<id1<<" "<<id2<<" "<<v2.result<<'\n';
	  v0.value1=v1.result;
	  v0.value2=v2.result;
	}
    }
  else if(b1.math and b2.constant)
    {
      // cout<<"b1.math and b2.constant"<<'\n';
      v0.mathOperator=operators.GetOperator(mathOperator);

      if(b2.negative)
	{
	  v0.value2Negative=1;
	  v0.value2=new double(constants[constantNames[s2.substr(1)]]);
	}
      else v0.value2=new double(constants[constantNames[s2]]);
      const VertexNew v1=vv[stoi(s1.substr(1, s1.size()-1))];
      v0.value1=v1.result;
    }
  else if(b1.math and b2.variable)
    {
      // cout<<"b1.math and b2.variable"<<'\n';
      v0.value2Negative=b2.negative;
      const uint8_t id2=data[(b2.negative)?s2.substr(1):s2];
      const uint8_t from2=(id2==0)?0:noOfInitialValue[id2-1];
      v0.value2=&variableValue[from2];
      v0.mathOperator=operators.GetOperator(mathOperator);
      const VertexNew v1=vv[stoi(s1.substr(1, s1.size()-1))];
      v0.value1=v1.result;
    }
  else if(b1.numeric and b2.math)
    {
      // cout<<"b1.numeric and b2.math "<<vv.size()<<" "<<stoi(s2.substr(1, s2.size()-1))<<'\n';
      v0.value1=new double(stod(s1));
      const uint8_t id2=stoi(s2.substr(1, s2.size()-1));
      const VertexNew v2=vv[id2];
      v0.mathOperator=operators.GetOperator(mathOperator);

      if(v2.result!=nullptr)
	{
	  cout<<"v2.result!=nullptr "<<*v2.result<<'\n';
	  v0.result=new double(operators.GetOperator(mathOperator)->Calculate(*v0.value1, *v2.result));
	  removeIndices.emplace_back(id2);
	  removeAddress.insert(v2.value1);
	  removeAddress.insert(v2.value2);
	  removeAddress.insert(v2.result);
	  // cout<<"result "<<*v0.result<<" "<<v0.result<<'\n';
	  // remove.emplace_back(id2);
	}
      else v0.value2=v2.result;
    }
  else if(b2.math and b1.constant)
    {
      // cout<<"b2.math and b1.constant "<<s1<<" "<<s2<<" "<<s2.substr(1, s2.size()-1)<<'\n';
      v0.mathOperator=operators.GetOperator(mathOperator);
      const uint8_t id2=stoi(s2.substr(1, s2.size()-1));
      const VertexNew v2=vv[id2];

      if(b1.negative)
	{
	  v0.value1Negative=1;
	  v0.value1=new double(constants[constantNames[s1.substr(1)]]);
	}
      else v0.value1=new double(constants[constantNames[s1]]);

      if(v2.result!=nullptr)
	{
	  cout<<"v2.result!=nullptr"<<'\n';
	  v0.result=new double(operators.GetOperator(mathOperator)->Calculate(*v0.value1, *v2.result));
	  removeIndices.emplace_back(id2);
	  removeAddress.insert(v2.value1);
	  removeAddress.insert(v2.value2);
	  removeAddress.insert(v2.result);
	  // cout<<"result "<<*v0.result<<'\n';
	  // remove.emplace_back(id2);
	}
      else v0.value2=v2.result;
    }
  else if(b2.math and b1.variable)
    {
      // cout<<"b2.math and b1.variable"<<'\n';
      v0.mathOperator=operators.GetOperator(mathOperator);
      const uint8_t id2=stoi(s2.substr(1, s2.size()-1));
      const VertexNew v2=vv[id2];
      v0.value1Negative=b1.negative;
      const uint8_t id1=data[(b1.negative)?s1.substr(1):s1];
      const uint8_t from1=(id1==0)?0:noOfInitialValue[id1-1];
      v0.value1=&variableValue[from1];
    }
  else if(b2.numeric and b1.math)
    {
      // cout<<"b2.numeric and b1.math"<<" "<<s1<<" "<<s2<<'\n';

      const uint8_t id1=stoi(s1.substr(1, s1.size()-1));
      const VertexNew v1=vv[id1];

      if(v1.result!=nullptr)
	{
	  cout<<"v1.result!=nullptr"<<'\n';
	  // cout<<*v1.result<<'\n';
	  v0.result=new double(operators.GetOperator(mathOperator)->Calculate(*v1.result, stod(s2)));
	  // cout<<"result "<<*v0.result<<'\n';
	  // remove.emplace_back(id1);
	  removeIndices.emplace_back(id1);
	  removeAddress.insert(v1.value1);
	  removeAddress.insert(v1.value2);
	  removeAddress.insert(v1.result);
	}
      else
	{
	  v0.mathOperator=operators.GetOperator(mathOperator);
	  v0.value1=v1.result;
	  v0.value2=new double(stod(s2));
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

Equations FileEquations::ParseEquations(map<string, uint16_t> &data, MathOperators &operators, double *variableValue, const vector<uint16_t> &noOfInitialValue)
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
      vector<uint8_t> removeIndices;
      std::unordered_set<double*> removeAddress;
      Equation equationNew;
      equationNew.id=id;

      for(const TestStr &eq: equation)
	{
	  const Bools b1(eq.str1, data, constantNames);
	  const Bools b2(eq.str2, data, constantNames);

	  CreateVertex(eq.str1, eq.str2, eq.op, b1, b2, operators, equationNew.vertices, variableValue, noOfInitialValue, data, removeIndices, removeAddress);
	}
      cout<<equationNew.vertices.size()<<'\n';
      cout<<"SIZES "<<removeAddress.size()<<" "<<removeIndices.size()<<'\n';
      // for(const auto &i: removeIndices)
      // 	{
      // 	  equationNew.vertices.erase(equationNew.vertices.begin()+i);
      // 	}

      // for(const auto &i: removeAddress)
      // 	{
      // 	  cout<<"first "<<i<<'\n';
      // 	  // delete i;
      // 	  // cout<<std::to_string(i)<<" Deleting "<<equationNew.vertices[i].value1<<" "<<equationNew.vertices[i].value2<<" "<<equationNew.vertices[i].result<<" "<<'\n';
      // 	  // delete equationNew.vertices[i].value1;
      // 	  // delete equationNew.vertices[i].value2;
      // 	  // delete equationNew.vertices[i].result;
      // 	  // equationNew.vertices.erase(equationNew.vertices.begin()+i);
      // 	}
      cout<<equationNew.vertices.size()<<'\n';
      equationNew.vertices.reserve(equationNew.vertices.size());
      equationsNew.equations.emplace_back(equationNew);
      cout<<" "<<'\n';
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
  cout<<"GetOrder "<<str<<'\n';

  while(str.size()>2)
    {
      uint8_t j=0;
      for(const string &i: OPERATORS)
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
      const string a3{str[at]};
      const TestStr LHS1{LHS, a3, RHS};

      a.emplace_back(LHS1);

      str.replace(str.begin()+size1-LHS.size(), str.begin()+size2, "@"+to_string(id));
      id++;
    }
  cout<<"-------------------------------------"<<'\n';
}

vector<TestStr> FileEquations::ToVector(string &eq)
{
  vector<string> equation;
  vector<TestStr> a;
  uint8_t id=0;

  RemoveOpenClose(eq, id, a);
  cout<<"EQ "<<eq<<'\n';
  GetOrder(eq, id, a);
  a.reserve(id);

  if(a.size()==0)
    {
      a.reserve(1);
      const TestStr mo{eq, "+", "0"};
      a.emplace_back(mo);
    }
  cout<<" "<<'\n';

  int j=0;

  for(const auto &i: a)
    {
      cout<<"@"<<j<<" "<<i.str1<<i.op<<i.str2<<'\n';
      j++;
    }
  return a;
}

FileEquations::FileEquations(const string &fileName)
{
  ReadFile(fileName);
}
