/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <algorithm>
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

using std::unordered_map;
using std::string;
using std::distance;
using std::vector;
using std::find;
using std::cout;

const vector<string> OPERATORS={"/", "*", "+", "-", "(", ")"};

int FindIndex(const string s)
{
  int found;
  int r=-1;
  int i=0;

  while(i<OPERATORS.size())
    {
      found=s.find(OPERATORS[i]);

      if(found==-1)
	{
	  i++;
	  continue;
	}
      else if(found<=r or r==-1) r=found;
      i++;
    }
  return r;
}

vector<string> ToVector(string v)
{
  int i;
  bool end=false;
  int size=v.size();
  string s;
  string mathop;
  vector<string> r;

  while(!end)
    {
      i=FindIndex(v);

      if(size>1)
	{
	  s=v.substr(0, i);
	  mathop=v[i];
	  v=v.substr(i+1, distance(v.begin()+1,v.end()));
	  if(!s.empty()) r.push_back(s);
	  if(find(OPERATORS.begin(), OPERATORS.end(), mathop) !=OPERATORS.end()) r.push_back(mathop);
	  size=v.size();
	}
      else if(size==1)
	{
	  r.push_back(v);
	  end=true;
	}
      else
	{
	  s=v[i];
	  r.push_back(s);
	  end=true;
	}
    }
  return r;
}
