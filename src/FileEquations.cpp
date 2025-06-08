#include "FileEquations.h"
#include "FileGraph.h"
#include "GraphEquation.h"

using std::to_string;

const string OPEN="(";
const string CLOSE=")";

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
  uint8_t open=str.find(OPEN);
  uint8_t openPrevious=open;
  // cout<<str<<'\n';
  // cout<<" "<<'\n';
  // cout<<"OPEN "<<std::to_string(open)<<" CLOSE "<<std::to_string(close)<<'\n';

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

  // cout<<std::to_string(open)<<" "<<std::to_string(openPrevious)<<" "<<std::to_string(close)<<'\n';
  return open;
}

void FileEquations::RemoveOpenClose(string &equation, uint8_t &id, vector<TestStr> &a)
{
  // bool stop=0;
  uint8_t close=equation.find(CLOSE);
  // uint8_t open=0;
  uint8_t open=GetOpen(equation, close);
  cout<<"RemoveOpenClose "<<equation<<'\n';
  while(open<equation.size())
    {
      open=GetOpen(equation, close);

      if(open>equation.size()) break;

      string sub1=equation.substr(open+1, close-open-1);
      GetOrder(sub1, id, a);

      equation.replace(equation.begin()+open, equation.begin()+close+1, "@"+std::to_string(id-1));

      cout<<equation<<" "<<sub1<<'\n';
      close=equation.find(CLOSE);
    }
  cout<<" "<<'\n';
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
  uint8_t i=distance(equation.begin(), std::find(equation.begin(), equation.end(), find));

  while(i<equation.size())
    {
      const string s1=equation[i-1];
      const string s2=equation[i+1];
      const string o=equation[i];
      const Bools b1(s1, data);
      const Bools b2(s2, data);

      graph->CreateEdge(s1, s2, o, b1, b2, id);

      // cout<<"Adding "<<"@"+to_string(id)<<"="<<s1<<o<<s2<<" "<<'\n';

      equation[i]="@"+to_string(id);
      equation.erase(equation.begin()+i+1);
      equation.erase(equation.begin()+i-1);

      // print_vector2(equation);
      id++;
      i=distance(equation.begin(), std::find(equation.begin(), equation.end(), find));
    }
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
      const Bools b(equation[0], data);
      graph=new GraphEquationSingle(b, equation[0]);
    }
  else if(size>2)
    {
      graph=new GraphEquation;
      id=test(equation, id, data, graph);
      id=ParseOperators(equation, id, data, size, graph);
    }
  // else error, size 2 is not allowed
}

map<uint16_t, GraphEquation*> FileEquations::ParseEquations(const vector<string> &data)
{
  // Set calculation order of an equation according to order of operations:

  // 1. Parentheses
  // 2. Exponents
  // 3. Multiplication and division
  // 4. Addition and subtraction

  // uint8_t id=0;
  // GraphEquation *graphEquation=nullptr;
  map<uint16_t, GraphEquation*> equations1;

  for(const auto& [name, v]: equations)
    {
      vector<string> equation=ToVector(v);
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

string FileEquations::print_vector3(const vector<string> &vec)
{
  uint8_t i=0;
  string empty="";
  const uint8_t size=vec.size();

  while(i<size)
    {
      // cout<<vec[i]<<'\n';
      if(i==0) empty=vec[i];
      // else empty=empty+";"+vec[i];
      else empty=empty+vec[i];
      i++;
    }
  // cout<<empty<<'\n';
  return empty;
}

uint8_t FileEquations::FindOperator(const string &eq)
{
  uint8_t smallest=eq.size();
  const string OPERATORS2[7]={"^", "/", "*", "+", "-", "(", ")"};
  const uint8_t size=smallest;

  for(const auto &i: OPERATORS2)
    {
      const uint8_t a=eq.find(i);

      if(a<size and a<smallest) smallest=a;
    }
  return smallest;
}

uint8_t FileEquations::FindOp(string &str)
{
  const string OPERATORS2[7]={"^", "/", "*", "+", "-", "(", ")"};
  uint8_t largest=0;
  uint8_t j=0;

  // while(j<7 and str.size()>2)
  while(j<7)
    {
      // cout<<"Now "<<str<<'\n';
      for(const auto &i: OPERATORS2)
	{
	  const uint8_t a=str.find(i);
	  // cout<<std::to_string(a)<<'\n';
	  if(a>largest and a<str.size())
	    {
	      largest=a;
	      // j=0;
	    }
	  else j++;
	}
      if(j==7) break;
      // cout<<"j "<<std::to_string(j)<<" "<<str.size()<<'\n';
      str.erase(str.begin(), str.begin()+largest+1);
      largest=0;
      j=0;
    }
  // cout<<str<<'\n';
  // cout<<" "<<'\n';
  return largest;
}

void FileEquations::GetOrder(string &str, uint8_t &id, vector<TestStr> &a)
{
  const string OPERATORS[5]={"^", "/", "*", "+", "-"};
  uint8_t at=0;
  cout<<"GetOrder "<<str<<'\n';

  while(str.size()>2)
    {
      for(const string &i: OPERATORS)
	{
	  at=str.find(i);
	  if(at<str.size()) break;
	}

      string a1=str.substr(0, at);
      const uint8_t size1=a1.size();
      const uint8_t from1=FindOp(a1);
      a1=a1.substr(from1);

      string a2=str.substr(at+1);
      const uint8_t to=FindOperator(a2);
      a2=a2.substr(0, to);
      TestStr a11;
      a11.str1=a1;
      a11.op=str[at];
      a11.str2=a2;

      a.emplace_back(a11);

      cout<<str<<" "<<str.size()<<" "<<size1-a1.size()<<" "<<at+a2.size()+1<<", "<<"|"<<a1<<":"<<str[at]<<":"<<a2<<"|"<<'\n';
      str.replace(str.begin()+size1-a1.size(), str.begin()+at+a2.size()+1, "@"+std::to_string(id));
      id++;
    }
  // if(str.size()<=3)
  cout<<"-------------------------------------"<<std::to_string(id)<<'\n';
  // cout<<str<<" "<<str.size()<<'\n';
}

vector<string> FileEquations::ToVector(string eq)
{
  // const string orig=eq;
  vector<string> equation;
  // uint8_t size=eq.size();

  // Check edge cases here
  // e.g. if smallest=0 and eq[smallest]=/, then it is illegal operation
  // if smallest=0 eq[smallest]=- is ok
  // Create a list of forbidden symbols and compare to them.
  vector<TestStr> a;
  uint8_t id=0;

  RemoveOpenClose(eq, id, a);
  cout<<"EQ "<<eq<<'\n';
  GetOrder(eq, id, a);
  cout<<" "<<'\n';
  int j=0;
  for(const auto &i: a)
    {
      cout<<"@"<<j<<" "<<i.str1<<i.op<<i.str2<<'\n';
      j++;
    }
  // const string orig=eq;
  // vector<string> equation;
  // uint8_t size=eq.size();

  // if(eq[0]=='-')
  //   {
  //     string eq1=eq;
  //     eq1.erase(eq1.begin());
  //     const uint8_t smallest1=FindOperator(eq1, size);
  //     const string str1=eq.substr(0, smallest1+1);
  //     equation.emplace_back(str1);
  //     eq.erase(eq.begin(), eq.begin()+smallest1+1);
  //   }

  // while(size>0)
  //   {
  //     size=eq.size();
  //     const uint8_t smallest=FindOperator(eq, size);

  //     if(smallest==size)
  // 	{
  // 	  equation.emplace_back(eq);
  // 	  break;
  // 	}
  //     else if(smallest>0)
  // 	{
  // 	  const string aa=eq.substr(0, smallest);
  // 	  equation.emplace_back(aa);
  // 	  const string s{eq[smallest]};
  // 	  equation.emplace_back(s);
  // 	  if(size>1)
  // 	    {
  // 	      eq.erase(eq.begin(), eq.begin()+smallest+1);
  // 	      // eq=eq.substr(smallest+1, size);
  // 	    }
  // 	}
  //     else
  // 	{
  // 	  const string s{eq[0]};
  // 	  equation.emplace_back(s);
  // 	  eq.erase(eq.begin());
  // 	}
  //   }

  // // auto a1=print_vector3(equation);
  // // if(a1==orig) cout<<"OK"<<'\n';
  // // else cout<<"NOT OK"<<'\n';
  // equation.reserve(equation.size());
  return equation;
}

FileEquations::FileEquations(const string &fileName)
{
  ReadFile(fileName);
}
