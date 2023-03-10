/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../class/SplittedString.h"

SplittedString split_string_in_two(string str, string splitter)
{
  int i=0;
  const string empty_str="";
  string empty=empty_str;
  string fchar;
  string str1;
  SplittedString rt;

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
  rt.splitted_string_part1=str1;
  rt.splitted_string_part2=empty;
  return rt;
}
