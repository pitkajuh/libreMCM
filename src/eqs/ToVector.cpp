/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

// #include "../types/Csv.h"
// #include "../types/AddSubtract.h"
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
  int r=0;
  int i=0;

  while(i<OPERATORS.size())
    {
      found=s.find(OPERATORS[i]);
      // cout<<"found "<<found<<" r "<<r<<'\n';
      // cout<<"r<found "<<r<<"<"<<found<<'\n';
      cout<<"found<r "<<found<<"<"<<r<<'\n';
      // if(r<found)
      if(found==-1)
	{
	  // cout<<"found>-1"<<'\n';
	  i++;
	  continue;
	}
      else// if(found<r)
	{
	  r=found;
	  cout<<"f="<<found<<" r="<<r<<'\n';
	  // cout<<"at "<<r<<'\n';
	}
      i++;
      cout<<" "<<'\n';
    }

  // while(r<found)
  //   {
  //     found=s.find(OPERATORS[i]);
  //     cout<<"found "<<found<<" r "<<r<<'\n';
  //     // if(r<found)
  //     // 	{
  //     // 	  r=found;
  //     // 	  cout<<"at "<<r<<'\n';
  //     // 	}
  //     i++;
  //   }

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
  cout<<v<<'\n';
  while(!end)
    {
      i=FindIndex(v);

      if(i>0 and size>1)
	{
	  s=v.substr(0, i);
	  mathop=v[i];
	  v=v.substr(i+1, distance(v.begin()+1,v.end()));
	  r.push_back(s);
	  if(find(OPERATORS.begin(), OPERATORS.end(), mathop) !=OPERATORS.end()) r.push_back(mathop);
	  size=v.size();
	}
      else
	{
	  s=v[i];
	  r.push_back(s);
	  end=true;
	}
    }

  for(const auto &u: r) cout<<"u "<<u<<'\n';
  cout<<" "<<'\n';
  return r;
}
