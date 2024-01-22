/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../global/global_constants.h"

const string line_remove_comment(const string line)
{
  int i=0;
  const int size=line.size();
  string fchar;
  string fchar_p1;
  string result;
  const string empty_string="";
  const string empty_string2=" ";
  const string empty_string3="\0";
  string line_return=empty_string;
  bool is_empty=line.empty();
  bool is_empty2;

  if(is_empty){result=line_return;}
  else
    {
      while(i<=size-1)
	{
	  fchar=line[i];
	  fchar_p1=line[i+1];
	  is_empty2=fchar.empty();

	  if(fchar==DIVIDE and fchar_p1==DIVIDE){break;}
	  else if(fchar==empty_string2 or fchar==empty_string3 or is_empty2)
	    {
	      i++;
	      continue;
	    }
	  else{line_return+=fchar;}
	  i++;
	}
      result=line_return;
    }
  return line_return;
}
