/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../global/global.h"

string line_remove_comment(string line)
{
  int i=0;
  string fchar;
  string fchar_p1;
  string result;
  const string empty_string="";
  const string empty_string2=" ";
  const string empty_string3="\0";
  string line_return=empty_string;

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
