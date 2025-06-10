#include "FileEquations.h"
#include "FileGraph.h"
#include "GraphEquation.h"

using std::to_string;

const string OPEN="(";
const string CLOSE=")";
const string OPERATORS2[7]={"^", "/", "*", "+", "-", OPEN, CLOSE};
const string OPERATORS[5]={"^", "/", "*", "+", "-"};

void FileEquations::print_vector2(const vector<string> &vec)
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

vector<string> FileEquations::GetParenthesis(const vector<string> &equation, const uint8_t open, const uint8_t close, uint8_t &id, const vector<string> &data, GraphEquation *&graph)
{
  vector<string> v1{equation.begin()+open+1, equation.begin()+close};
  id=ParseOperators(v1, id, data, v1.size(), graph);
  id=test(v1, id, data, graph);
  const vector<string> v2{equation.begin(), equation.begin()+open};
  const vector<string> v3{equation.begin()+close+1, equation.end()};
  vector<string> result;
  result.reserve(v1.size()+v2.size()+v3.size());

  result.insert(result.begin(), v2.begin(), v2.end());
  result.insert(result.end(), v1.begin(), v1.end());
  result.insert(result.end(), v3.begin(), v3.end());
  // print_vector2(result);
  return result;
}

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

void FileEquations::Remove(string &equation, const uint8_t open, const uint8_t close)
{
  // if(equation[open+1]=='(' and equation[close+1]==')')
  //   {
  //     equation.erase(equation.begin()+open);
  //     equation.erase(equation.begin()+close-1);
  //     RemoveOpenClose(equation);
  //   }
}

void FileEquations::RemoveOpenClose(vector<string> &equation)
{
  // Removes unnecessary parenthesis from equations such as ((1+(a+b)))
  const uint8_t open=distance(equation.begin(), find(equation.begin(), equation.end(), OPEN));
  const uint8_t close=distance(equation.begin(), find(equation.begin(), equation.end(), CLOSE));
  if(open!=equation.size() and close!=equation.size()) Remove(equation, open, close);
}

void FileEquations::Remove(vector<string> &equation, const uint8_t open, const uint8_t close)
{
  if(equation[open+1]==OPEN and equation[close+1]==CLOSE)
    {
      equation.erase(equation.begin()+open);
      equation.erase(equation.begin()+close-1);
      RemoveOpenClose(equation);
    }
}

uint8_t FileEquations::test2(vector<string> &equation, uint8_t open, uint8_t close, uint8_t id, const vector<string> &data, GraphEquation *&graph)
{
  vector<string> tmp={equation.begin()+open+1, equation.begin()+close};
  uint8_t op=distance(tmp.begin(), find(tmp.begin(), tmp.end(), OPEN));

  while(op<tmp.size())
    {
      open=distance(equation.begin()+open+1, find(equation.begin()+open+1, equation.end(), OPEN))+open+1;
      equation=GetParenthesis(equation, open, close, id, data, graph);
      open=distance(equation.begin(), find(equation.begin(), equation.end(), OPEN));
      close=distance(equation.begin(), find(equation.begin(), equation.end(), CLOSE));
      tmp={equation.begin()+open+1, equation.begin()+close};
      op=distance(tmp.begin(), find(tmp.begin(), tmp.end(), OPEN));
    }
  return id;
}

uint8_t FileEquations::test(vector<string> &equation, uint8_t id, const vector<string> &data, GraphEquation *&graph)
{
  uint8_t open=distance(equation.begin(), find(equation.begin(), equation.end(), OPEN));

  while(open<equation.size())
    {
      const uint8_t close=distance(equation.begin(), find(equation.begin(), equation.end(), CLOSE));
      const vector<string> tmp={equation.begin()+open+1, equation.begin()+close};

      const uint8_t op=distance(tmp.begin(), find(tmp.begin(), tmp.end(), OPEN));
      if(op==tmp.size()) equation=GetParenthesis(equation, open, close, id, data, graph);
      else id=test2(equation, open, close, id, data, graph);
      open=distance(equation.begin(), find(equation.begin(), equation.end(), OPEN));
    }
  return id;
}

uint8_t FileEquations::FindOperator(vector<string> &equation, const string &find, uint8_t id, const vector<string> &data, GraphEquation *&graph)
{
  // uint8_t i=distance(equation.begin(), std::find(equation.begin(), equation.end(), find));

  // while(i<equation.size())
  //   {
  //     const string s1=equation[i-1];
  //     const string s2=equation[i+1];
  //     const string o=equation[i];
  //     const Bools b1(s1, data);
  //     const Bools b2(s2, data);

  //     graph->CreateEdge(s1, s2, o, b1, b2, id);

  //     // cout<<"Adding "<<"@"+to_string(id)<<"="<<s1<<o<<s2<<" "<<'\n';

  //     equation[i]="@"+to_string(id);
  //     equation.erase(equation.begin()+i+1);
  //     equation.erase(equation.begin()+i-1);

  //     // print_vector2(equation);
  //     id++;
  //     i=distance(equation.begin(), std::find(equation.begin(), equation.end(), find));
  //   }
  return id;
}

uint8_t FileEquations::ParseOperators(vector<string> &equation, uint8_t id, const vector<string> &data, const uint8_t size, GraphEquation *&graph)
{
  const string OPERATORS[5]={"^", "/", "*", "+", "-"};

  for(const auto &i: OPERATORS)
    {
      id=FindOperator(equation, i, id, data, graph);
    }
  return id;
}

void FileEquations::GetOrder(vector<string> &equation, uint8_t id, const vector<string> &data, GraphEquation *&graph)
{
  const uint8_t size=equation.size();

  if(size==1)
    {
      // const Bools b(equation[0], data);
      // graph=new GraphEquationSingle(b, equation[0]);
    }
  else if(size>2)
    {
      graph=new GraphEquation;
      id=test(equation, id, data, graph);
      id=ParseOperators(equation, id, data, size, graph);
    }
  // else error, size 2 is not allowed
}

void FileEquations::CreateVertex(const string &s1, const string &s2, const string &mathOperator, const Bools &b1, const Bools &b2, MathOperators &operators, vector<VertexNew> &vv)
{
  cout<<"Create "<<s1<<mathOperator<<s2<<'\n';

    if(b1.variable and b2.variable)
    {
      cout<<"b1.variable and b2.variable"<<'\n';
      // CreateVertex<VertexVariable, VertexVariable>(s1, s2, mathOperator, id, vmap, variables, variables);
    }
  else if(b1.variable and b2.constant)
    {
      cout<<"if(b1.variable and b2"<<'\n';
      // CreateVertex<VertexVariable, VertexConstant>(s1, s2, mathOperator, id, vmap, variables, constants);
    }
  else if(b1.variable and b2.numeric)
    {
      cout<<"if(b1.variable and b2"<<'\n';
      // CreateVertexNumeric<VertexVariable, VertexVerticesNumeric2>(s2, s1, mathOperator, id, variables, vmap);
    }
  else if(b1.constant and b2.variable)
    {
      cout<<"b1.constant and b2.variable"<<'\n';
      // CreateVertex<VertexConstant, VertexVariable>(s1, s2, mathOperator, id, vmap, constants, variables);
    }
  else if(b1.constant and b2.constant)
    {
      cout<<"b1.constant and b2.constant"<<'\n';
      // CreateVertex<VertexConstant, VertexConstant>(s1, s2, mathOperator, id, vmap, constants, constants);
    }
  else if(b1.constant and b2.numeric)
    {
      cout<<"b1.constant and b2.numeric"<<'\n';
      // CreateVertexNumeric<VertexConstant, VertexVerticesNumeric2>(s2, s1, mathOperator, id, constants, vmap);
    }
  else if(b1.numeric and b2.variable)
    {
      cout<<"b1.numeric and b2.variable"<<'\n';
      // CreateVertexNumeric<VertexVariable, VertexVerticesNumeric1>(s1, s2, mathOperator, id, variables, vmap);
    }
  else if(b1.numeric and b2.constant)
    {
      cout<<"b1.numeric and b2.constant"<<'\n';
      // CreateVertexNumeric<VertexConstant, VertexVerticesNumeric1>(s1, s2, mathOperator, id, constants, vmap);
    }
  else if(b1.numeric and b2.numeric)
    {
      // Result can be calculated in advance, so the equation template can
      // be simplified and performance of the calculation increased.
      cout<<"b1.numeric and b2.numeric "<<s1<<" "<<s2<<'\n';
      VertexNew v1;
      double d=operators.GetOperator(mathOperator)->Calculate(stod(s1), stod(s2));
      v1.result=&d;
      vv.emplace_back(v1);
      // VertexValue *vertex1=new VertexNumeric(s1);
      // VertexValue *vertex2=new VertexNumeric(s2);
      // VertexVertices *v=new VertexVertices(vertex1, vertex2, mathOperator);
      // v->Calculate();
      // VertexValue *calculated=new VertexNumeric(v->GetValue());

      // // vmap["@"+std::to_string(id)]=calculated;
      // vmap.emplace_back(calculated);
      // delete vertex1;
      // delete vertex2;
      // delete v;
      // // cout<<calculated<<'\n';
    }
  else if(b1.math and b2.math)
    {
      cout<<"b1.math and b2.math "<<'\n';
      // VertexVertices *v1=new VertexVertices(vmap[stoi(s1.substr(1, s1.size()-1))], vmap[stoi(s2.substr(1, s1.size()-1))], mathOperator);
      // vmap["@"+std::to_string(id)]=v1;
      // vmap.emplace_back(v1);
    }
  else if(b1.math and b2.constant)
    {
      cout<<"b1.math and b2.constant"<<'\n';
      // AddMath<VertexConstant, vector<Vertex*>, map<string, Vertex*>, string, Vertex*>(s2, mathOperator, id, vmap, constants, !IsInMap(s2, constants), s2, vmap[stoi(s1.substr(1, s1.size()-1))]);
    }
  else if(b1.math and b2.variable)
    {
      cout<<"b1.math and b2.variable"<<'\n';
      // AddMath<VertexVariable, vector<Vertex*>, map<string, Vertex*>, string, Vertex*>(s2, mathOperator, id, vmap, variables, !IsInMap(s2, variables), s2, vmap[stoi(s1.substr(1, s1.size()-1))]);
    }
  else if(b1.numeric and b2.math)
    {
      cout<<"b1.numeric and b2.math and vmap[s2]->GetValue()!=NAN"<<'\n';
      // Result can be calculated in advance, so the equation template can
      // be simplified and performance of the calculation increased.
      // CreateMath(s2, s1, mathOperator, id);
      VertexNew v0;
      // double d=stod(s1);
      // v0.value1=&d;

      VertexNew v1=vv[stoi(s2.substr(1, s2.size()-1))];

      // v0.value2=v1.result;


      double d=operators.GetOperator(mathOperator)->Calculate(stod(s1), *v1.result);
      v0.result=&d;
    }
  else if(b2.math and b1.constant)
    {
      cout<<"b2.math and b1.constant "<<s1<<" "<<s2<<" "<<s2.substr(1, s2.size()-1)<<'\n';

      // const int8_t id1=stoi(s2.substr(1, s2.size()-1));
      // const int8_t id2=constants.size();

      // AddMath2<VertexConstant, map<string, Vertex*>, vector<Vertex*>, int8_t, Vertex*>(s2, mathOperator, id, constants, vmap, id2<id1, id1, constants[s1]);
    }
  else if(b2.math and b1.variable)
    {
      cout<<"b2.math and b1.variable"<<'\n';

      // const int8_t id1=stoi(s2.substr(1, s2.size()-1));
      // const int8_t id2=vmap.size();

      // AddMath2<VertexConstant, map<string, Vertex*>, vector<Vertex*>, uint8_t, Vertex*>(s2, mathOperator, id, variables, vmap, id2<id1, id1, variables[s1]);
    }
  else if(b2.numeric and b1.math)
    {
      cout<<"b2.numeric and b1.math and vmap[s1]->GetValue()!=NAN"<<" "<<s1<<" "<<s2<<'\n';
      // Result can be calculated in advance, so the equation template can
      // be simplified and performance of the calculation increased.
      // CreateMath(s1, s2, mathOperator, id);
    }
  else if(!b1.variable and !b1.constant and !b1.numeric and !b1.math)
    {
      throw std::invalid_argument("Value \""+s1+"\" is not a constant, variable or numeric value.");
    }
  else
    {
      throw std::invalid_argument("Value \""+s2+"\" is not a constant, variable or numeric value.");
    }
}

map<uint16_t, GraphEquation*> FileEquations::ParseEquations(const vector<string> &data, MathOperators &operators)
{
  // Set calculation order of an equation according to order of operations:

  // 1. Parentheses
  // 2. Exponents
  // 3. Multiplication and division
  // 4. Addition and subtraction

  GraphEquation *graphEquation=nullptr;
  map<uint16_t, GraphEquation*> equations1;

  for(const auto& [name, v]: equations)
    {
      const vector<TestStr> equation=ToVector(v);
      vector<VertexNew> vv;

      for(const TestStr &eq: equation)
	{
	  const string s1=eq.str1;
	  const string s2=eq.str2;
	  const string o=eq.op;
	  const Bools b1(s1, data, constantNames);
	  const Bools b2(s2, data, constantNames);

	  CreateVertex(s1, s2, o, b1, b2, operators, vv);
	}
      // vv.clear();
      // RemoveOpenClose(equation);
      // cout<<"EQUATION"<<'\n';
      // print_vector2(equation);
      // GetOrder(equation, id, data, graphEquation);
      // // print_vector2(equation);
      // id=0;
      // equations1[name]=graphEquation;
      // graphEquation=nullptr;
      // cout<<"ok"<<'\n';

      cout<<" "<<'\n';
    }
  equations.clear();
  return equations1;
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

vector<TestStr> FileEquations::ToVector(string eq)
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
