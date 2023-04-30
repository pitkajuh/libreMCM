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

const string remove_white_space(const string line)
{
  int i=0;
  bool is_empty;
  const int size=line.size()-1;
  const string empty_str="";
  const string empty_str2=" ";
  const string empty_str3="\0";
  const string empty_str4="\t";
  string rt;
  string fchar;

  if(size==0)
    {
      rt=line;
    }
  else
    {
      while(i<=size)
	{
	  fchar=line[i];
	  is_empty=fchar.empty();

	  if(fchar==empty_str4 or fchar==empty_str2 or fchar==empty_str3 or is_empty)
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
