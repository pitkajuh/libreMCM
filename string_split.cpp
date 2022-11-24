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
#include <tuple>

using namespace std;

tuple<string, string> split_string_in_two(string str, string splitter)
{
  int i=0;
  string empty="", fchar, str1;

  while(i<=str.size()-1)
    {
      fchar=str[i];

      if(fchar==splitter)
	{
	  str1=empty;
	  empty="";
	}
      else
	{
	  empty=empty+fchar;
	}
      i++;
    }

  return make_tuple(str1, empty);
}
