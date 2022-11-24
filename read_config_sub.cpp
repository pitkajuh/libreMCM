/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <iostream>
#include <tuple>
#include "global.h"

using namespace std;

string remove_white_space(string line)
{
  int i=0;
  string rt="", fchar;

  if(line.size()==0)
    {
      rt=line;
    }
  else
    {
      while(i<=line.size()-1)
	{
	  fchar=line[i];

	  if(fchar==" " or fchar=="\0" or fchar.empty())
	    {
	      i++;
	      continue;
	    }
	  else
	    {
	      rt=rt+fchar;
	    }
	  i++;
	}
    }
  return rt;
}

tuple<string, string> read_constants(string line)
{
  int i;
  string fchar, ab, empty_str="", constant_name, value;
  bool eq_found=false;
  tuple<string, string> values1;
  string constant_value;

  while(i<=line.size()-1)
    {
      if(line[i]==';')
	{
	  constant_value=ab;
	}
     if(line[i]=='=')
	{
	  constant_name=ab;
	  ab=empty_str;
	  eq_found=true;
	  i++;
	}
      if(isblank(line[i]) or line[i]=='\0')
	{
	  i++;
	  continue;
	}
      else
	{
	  ab=ab+line[i];
	}
      i++;
    }

  values1=make_tuple(constant_name, constant_value);
  return values1;
}

string line_commented_or_not(string line)
{
  int i=0, index_from, index_to;
  string fchar, fchar_p1, line_return="", empty="", empty2=" ";

  while(i<=line.size()-1)
    {
      fchar=line[i];
      fchar_p1=line[i+1];

      if(fchar==divide and fchar_p1==divide)
	{
	  break;
	}
      else if(fchar==" " or fchar=="\0" or fchar.empty())
	{
	  i++;
	  continue;
	}
      else
	{
	  line_return=line_return+line[i];
	}
      i++;
    }

  return line_return;
}
