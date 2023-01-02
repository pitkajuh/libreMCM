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
  const string empty_str="";
  const string empty_str2=" ";
  const string empty_str3="\0";
  string rt=empty_str;
  string fchar;

  if(line.size()==0)
    {
      rt=line;
    }
  else
    {
      while(i<=line.size()-1)
	{
	  fchar=line[i];

	  if(fchar==empty_str2 or fchar==empty_str3 or fchar.empty())
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
  const string empty_str_const="";
  string ab;
  string empty_str=empty_str_const;
  string constant_name;
  string line_i_str;
  char line_i;
  bool eq_found=false;
  tuple<string, string> values1;
  string constant_value;
  const char empty_char='\0';
  const char delimiter_char=';';
  const char equal_sign_char='=';

  while(i<=line.size()-1)
    {
      line_i=line[i];

      if(line_i==delimiter_char)
	{
	  constant_value=ab;
	}

      if(line_i==equal_sign_char)
	{
	  constant_name=ab;
	  ab=empty_str;
	  eq_found=true;
	  i++;
	}

      if(isblank(line_i) or line_i==empty_char)
	{
	  i++;
	  continue;
	}
      else
	{
	  line_i_str=line[i];
	  ab=ab+line_i_str;
	}
      i++;
    }

  values1=make_tuple(constant_name, constant_value);

  return values1;
}

string line_commented_or_not(string line)
{
  int i=0;
  string fchar;
  string fchar_p1;
  const string empty_string="";
  const string empty_string2=" ";
  const string empty_string3="\0";
  string line_return=empty_string;
  string result;

  if(line.empty())
    {
      result=line_return;
    }
  else
    {
      while(i<=line.size()-1)
	{
	  fchar=line[i];
	  fchar_p1=line[i+1];

	  if(fchar==divide and fchar_p1==divide)
	    {
	      break;
	    }
	  else if(fchar==empty_string2 or fchar==empty_string3 or fchar.empty())
	    {
	      i++;
	      continue;
	    }
	  else
	    {
	      line_return=line_return+fchar;
	    }
	  i++;
	}

      result=line_return;
    }

  return line_return;
}
