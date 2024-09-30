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

void StringConvert(string v, vector<string> &aa)
{
  const int16_t i=FindIndex(v);

  if(i<v.size())
    {
      const string s=v.substr(0, i);
      const string mathop{v[i]};
       if(!s.empty()) aa.emplace_back(s);
      aa.emplace_back(mathop);
      v=v.substr(i+1, std::distance(v.begin()+1,v.end()));
      StringConvert(v, aa);
    }
  // else if(!v.empty()) aa.emplace_back(v);
  else aa.emplace_back(v);
}

vector<string> ToVector(string v)
{
  const uint16_t size=v.size();
  assert(size!=2 and size>0 && "The equation {v} is too short.");
  vector<string> r;
  StringConvert(v, r);
  assert(v.size()<=UINT8_MAX && "Equation size limit exceeded!");
  return r;
}
