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
  const string empty_str="";
  string empty=empty_str;
  string fchar;
  string str1;
  tuple<string, string> rt;

  while(i<=str.size()-1)
    {
      fchar=str[i];

      if(fchar==splitter)
	{
	  str1=empty;
	  empty=empty_str;
	}
      else
	{
	  empty=empty+fchar;
	}

      i++;

    }

  rt=make_tuple(str1, empty);

  return rt;
}
