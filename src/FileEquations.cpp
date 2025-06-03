#include "FileEquations.h"

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
