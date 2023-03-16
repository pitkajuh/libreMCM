/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <string>

using std::string;

string remove_white_space(const string line)
{
  int i=0;
  const int size=line.size();
  const string empty_str="";
  const string empty_str2=" ";
  const string empty_str3="\0";
  string rt=empty_str;
  string fchar;
  bool is_empty;

  if(size==0)
    {
      rt=line;
    }
  else
    {
      while(i<=size-1)
	{
	  fchar=line[i];
	  is_empty=fchar.empty();

	  if(fchar==empty_str2 or fchar==empty_str3 or is_empty)
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
