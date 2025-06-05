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
  ParseOperators(v1, id, data, v1.size(), graph);
  test(v1, id, data, graph);
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

vector<string> FileEquations::RemoveOpenClose(vector<string> &equation)
{
  // Removes unnecessary parenthesis from equations such as ((1+(a+b)))
  const uint8_t open=distance(equation.begin(), find(equation.begin(), equation.end(), OPEN));
  const uint8_t close=distance(equation.begin(), find(equation.begin(), equation.end(), CLOSE));
  if(open!=equation.size() and close!=equation.size()) Remove(equation, open, close);
  return equation;
}

void FileEquations::Remove(vector<string> &equation, const uint8_t open, const uint8_t close)
{
  if(equation[open+1]==OPEN and equation[close+1]==CLOSE)
    {
      equation.erase(equation.begin()+open);
      equation.erase(equation.begin()+close-1);
      equation=RemoveOpenClose(equation);
    }
}

const bool FileEquations::IsOpen(const vector<string> &tmp)
{
  const uint8_t op=distance(tmp.begin(), find(tmp.begin(), tmp.end(), OPEN));

  if(op==tmp.size()) return 1;
  return 0;
}

void FileEquations::test2(vector<string> &equation, uint8_t open, uint8_t close, uint8_t &id, const vector<string> &data, GraphEquation *&graph)
{
  const vector<string> tmp={equation.begin()+open+1, equation.begin()+close};
  const uint8_t op=distance(tmp.begin(), find(tmp.begin(), tmp.end(), OPEN));

  if(op<tmp.size())
    {
      open=distance(equation.begin()+open+1, find(equation.begin()+open+1, equation.end(), OPEN))+open+1;
      equation=GetParenthesis(equation, open, close, id, data, graph);
      open=distance(equation.begin(), find(equation.begin(), equation.end(), OPEN));
      close=distance(equation.begin(), find(equation.begin(), equation.end(), CLOSE));
      test2(equation, open, close, id, data, graph);
    }
}

void FileEquations::test(vector<string> &equation, uint8_t &id, const vector<string> &data, GraphEquation *&graph)
{
  uint8_t open=distance(equation.begin(), find(equation.begin(), equation.end(), OPEN));

  while(open<equation.size())
    {
      const uint8_t close=distance(equation.begin(), find(equation.begin(), equation.end(), CLOSE));
      const vector<string> tmp={equation.begin()+open+1, equation.begin()+close};

      if(IsOpen(tmp)) equation=GetParenthesis(equation, open, close, id, data, graph);
      else test2(equation, open, close, id, data, graph);
      open=distance(equation.begin(), find(equation.begin(), equation.end(), OPEN));
    }
}

void FileEquations::FindOperator(vector<string> &equation, const string &find, uint8_t &id, const vector<string> &data, GraphEquation *&graph)
{
  const uint8_t i=distance(equation.begin(), std::find(equation.begin(), equation.end(), find));

  if(i<equation.size())
    {
      const string s1=equation[i-1];
      const string s2=equation[i+1];
      const string o=equation[i];
      const Bools b1(s1, data);
      const Bools b2(s2, data);

      graph->CreateEdge(s1, s2, o, b1, b2, id);

      cout<<"Adding "<<"@"+to_string(id)<<"="<<s1<<o<<s2<<" "<<'\n';

      equation[i]="@"+to_string(id);
      equation.erase(equation.begin()+i+1);
      equation.erase(equation.begin()+i-1);

      print_vector2(equation);
      id++;
      FindOperator(equation, find, id, data, graph);
    }
}

void FileEquations::ParseOperators(vector<string> &equation, uint8_t &id, const vector<string> &data, const uint8_t size, GraphEquation *&graph)
{
  const string OPERATORS[5]={"^", "/", "*", "+", "-"};

  for(const auto &i: OPERATORS)
    {
      FindOperator(equation, i, id, data, graph);
    }
}

void FileEquations::GetOrder(vector<string> &equation, uint8_t &id, const vector<string> &data, GraphEquation *&graph)
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
      test(equation, id, data, graph);
      ParseOperators(equation, id, data, size, graph);
    }
  // else error, size 2 is not allowed
}

map<string, GraphEquation*> FileEquations::ParseEquations(const vector<string> &data)
{
  // Set calculation order of an equation according to order of operations:

  // 1. Parentheses
  // 2. Exponents
  // 3. Multiplication and division
  // 4. Addition and subtraction

  vector<string> v;
  uint8_t id=0;
  GraphEquation *graphEquation=nullptr;
  map<string, GraphEquation*> equations;

  for(auto& [name, equation]: equations2)
    {
      // v=ToVector(equation);
      v=RemoveOpenClose(equation);
      cout<<"EQUATION"<<'\n';
      print_vector2(v);
      GetOrder(v, id, data, graphEquation);

      // head->next=nullptr;
      // equationMap[name]=head;
      id=0;
      equations[name]=graphEquation;
      // delete graphEquation;
      graphEquation=nullptr;
      cout<<"ok"<<'\n';

      cout<<" "<<'\n';
    }
  return equations;
}

void FileEquations::Convert(const map<string, string> &map)
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
      Convert(GetSettings(result.second));
    }
  else if(sub==equations1)
    {
      result=ReadContent(file, from, equations1, 9);
      equations=GetSettings(result.second);
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

unsigned FileEquations::FindOperator(const string &eq, const unsigned size)
{
  unsigned smallest=size;
  const string OPERATORS2[7]={"^", "/", "*", "+", "-", "(", ")"};

  for(const auto &i: OPERATORS2)
    {
      const unsigned a=eq.find(i);

      if(a<size and a<smallest) smallest=a;
    }
  return smallest;
}

vector<string> FileEquations::ToVector(string eq)
{
  const string orig=eq;
  vector<string> equation;
  unsigned size=eq.size();

  // Check edge cases here
  // e.g. if smallest=0 and eq[smallest]=/, then it is illegal operation
  // if smallest=0 eq[smallest]=- is ok
  // Create a list of forbidden symbols and compare to them.

  if(eq[0]=='-')
    {
      string eq1=eq;
      eq1.erase(eq1.begin());
      const unsigned smallest1=FindOperator(eq1, size);
      const string str1=eq.substr(0, smallest1+1);
      equation.emplace_back(str1);
      eq=eq.substr(smallest1+1, size);
    }

  while(size>0)
    {
      size=eq.size();
      const unsigned smallest=FindOperator(eq, size);

      if(smallest==size)
	{
	  equation.emplace_back(eq);
	  break;
	}
      else if(smallest>0)
	{
	  const string aa=eq.substr(0, smallest);
	  equation.emplace_back(aa);
	  const string s{eq[smallest]};
	  equation.emplace_back(s);
	  if(size>1) eq=eq.substr(smallest+1, size);
	}
      else
	{
	  const string s{eq[0]};
	  equation.emplace_back(s);
	  eq.erase(eq.begin());
	}
    }

  auto a1=print_vector3(equation);
  if(a1==orig) cout<<"OK"<<'\n';
  else cout<<"NOT OK"<<'\n';
  return equation;
}

FileEquations::FileEquations(const string &fileName)
{
  ReadFile(fileName);
  for(const auto &[i, v]: constants)
    {
      cout<<i<<" "<<v<<'\n';
    }
  cout<<" "<<'\n';
  for(auto &[i, v]: equations)
    {
      cout<<v<<" "<<v.size()<<'\n';
      cout<<i<<" "<<v<<'\n';
      equations2[i]=ToVector(v);
      cout<<" "<<'\n';
    }
  equations.clear();
}
