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
void print_vector3(const vector<string> &vec)
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

const int16_t FindIndexSub(const string &s, int16_t i)
{
  const int16_t found=s.find(OPERATORS2[i]);
  const int16_t size=OPERATORS2.size();

  if (found==-1 and i<size)
    {
      i++;
      return FindIndexSub(s, i);
    }
  return i;
}

const int16_t FindIndex(const string &s)
{
  const uint8_t size=OPERATORS2.size();
  int16_t r=-1;
  int16_t i=0;
  int16_t found;

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

const bool Rules(string &v, const int16_t i, vector<string> &aa, uint8_t &t)
{
  if(i==0 and t==0 and v[i]=='-' and v[i+1]!='(')
    {
      return 1;
    }
  return 0;
}

void StringConvert(string &v, vector<string> &aa, uint8_t &t)
{
  const int16_t i=FindIndex(v);
  const uint8_t size1=v.size();
  const bool rule=Rules(v, i, aa, t);

  if(rule)
    {
      const int16_t j=FindIndex(v.substr(i+1, std::distance(v.begin()+1,v.end())));
      cout<<i<<" "<<j<<'\n';
      const string mathop{v[j+1]};

      const string test=v.substr(0, j+1);
      v=v.substr(j+2, std::distance(v.begin()+1,v.end()));
      aa.emplace_back(test);
      cout<<"try "<<test<<";"<<mathop<<";"<<v<<'\n';
      t=size1-v.size();
      aa.emplace_back(mathop);
      StringConvert(v, aa, t);
    }
  else if(i>-1)
    {
      const string s=v.substr(0, i);
      const string mathop{v[i]};
       if(!s.empty()) aa.emplace_back(s);
      aa.emplace_back(mathop);
      v=v.substr(i+1, std::distance(v.begin()+1,v.end()));
      t=size1-v.size();
      StringConvert(v, aa, t);
    }
  else if(!v.empty()) aa.emplace_back(v);
}

vector<string> ToVector(string v)
{
  cout<<v<<'\n';
  vector<string> r;
  uint8_t t=0;
  StringConvert(v, r, t);
  const uint8_t size=r.size();
  cout<<v<<" "<<std::to_string(size)<<" "<<UINT8_MAX<<'\n';
  assert(size>0 && "The equation is too short.");
  assert(size<=UINT8_MAX && "Equation size limit exceeded!");

  return r;
}
