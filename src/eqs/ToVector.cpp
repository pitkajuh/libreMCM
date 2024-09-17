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
#include <cstdint>
#include <cassert>

using std::vector;
using std::find;
#include <iostream>
using std::cout;
void print_vector3(vector<string> &vec)
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
int8_t FindIndex(const string &s)
{
  const uint8_t size=OPERATORS2.size();
  int8_t r=-1;
  int8_t i=0;
  int8_t found;

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
  int16_t i;
  bool end=false;
  uint16_t size=v.size();
  string s;
  string mathop;
  vector<string> r;

  // assert(size!=2 and size>0 && "The equation {v} is too short.");
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
	  if(!s.empty()) r.emplace_back(s);
	  if(find(OPERATORS2.begin(), OPERATORS2.end(), mathop)!=OPERATORS2.end()) r.emplace_back(mathop);
	  size=v.size();
	}
      else if(size==1)
	{
	  r.emplace_back(v);
	  end=true;
	}
      else if(i>-1 and size!=1)
	{
	  s=v[i];
	  r.emplace_back(s);
	  end=true;
	}
      else end=true;
    }
  assert(v.size()<=UINT8_MAX);

  return r;
}
