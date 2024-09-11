/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../global/mathconst.h"
#include <algorithm>
#include <vector>

using std::vector;
using std::find;
#include <iostream>
using std::cout;
void print_vector3(vector<string> vec)
{
  int i=0;
  string empty="";

  while(i<=vec.size()-1 && vec.size()>0)
    {
      if(i==0)  empty=vec[i];
      else empty=empty+";"+vec[i];
      i++;
    }
  cout<<empty<<'\n';
}
int FindIndex(const string &s)
{
  const unsigned size=OPERATORS2.size();
  int r=-1;
  unsigned i=0;
  unsigned found;

  while(i<size)
    {
      found=s.find(OPERATORS2[i]);

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
  unsigned size=v.size();
  string s;
  string mathop;
  vector<string> r;
  // cout<<v<<'\n';
  // while(size!=1)
  //   {
  //     i=FindIndex(v);
  //     // cout<<i+1<<"/"<<size<<'\n';
  //     s=v.substr(0, i);
  //     mathop=v[i];
  //     r.emplace_back(s);
  //     r.emplace_back(mathop);
  //     // cout<<s<<" "<<mathop<<'\n';
  //     v=v.substr(i+1, std::distance(v.begin()+1,v.end()));
  //     size=v.size();
  //     // cout<<v<<'\n';
  //     // print_vector3(r);
  //     // size=1;
  //   }

  while(!end)
    {
      i=FindIndex(v);

      if(size>1)
	{
	  s=v.substr(0, i);
	  mathop=v[i];
	  v=v.substr(i+1, std::distance(v.begin()+1,v.end()));
	  if(!s.empty())
	    {
	      r.emplace_back(s);
	    }
	  if(find(OPERATORS2.begin(), OPERATORS2.end(), mathop)!=OPERATORS2.end())
	    {
	      // cout<<"find(OPERATORS2.begin(), OPERATORS2.end(), mathop) !=OPERATORS2.end()"<<'\n';
	      r.emplace_back(mathop);
	      // print_vector3(r);
	    }
	  size=v.size();
	}
      else if(size==1)
	{
	  // cout<<"size==1"<<'\n';
	  r.emplace_back(v);
	  // print_vector3(r);
	  end=true;
	}
      else if(i>-1 and size!=1)
	{
	  // cout<<"i>-1 and size!=1"<<'\n';
	  s=v[i];
	  r.emplace_back(s);
	  // print_vector3(r);
	  end=true;
	}
      else end=true;
    }
  return r;
}
