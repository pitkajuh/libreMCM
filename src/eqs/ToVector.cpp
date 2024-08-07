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

int FindIndex(const string &s)
{
  int r=-1;
  unsigned int i=0;
  unsigned int found;

  while(i<OPERATORS2.size())
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
  unsigned int size=v.size();
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
	  v=v.substr(i+1, std::distance(v.begin()+1,v.end()));
	  if(!s.empty()) r.emplace_back(s);
	  if(find(OPERATORS2.begin(), OPERATORS2.end(), mathop) !=OPERATORS2.end()) r.emplace_back(mathop);
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
  return r;
}
