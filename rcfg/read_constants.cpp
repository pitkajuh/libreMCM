/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../class/ConstantNameAndValue.h"
#include "../util/remove_white_space.h"
#include "../util/line_remove_comment.h"
#include "../global/global.h"

ConstantNameAndValue read_constants(string line)
{
  int i;
  int size=line.size();
  string ab;
  string empty_str="";
  string constant_name;
  string line_i_str;
  string constant_value;
  char line_i;
  bool is_empty;
  const char empty_char='\0';
  const char delimiter_char=';';
  const char equal_sign_char='=';
  ConstantNameAndValue values1;

  while(i<=size-1)
    {
      line_i=line[i];
      is_empty=isblank(line_i);

      if(is_empty or line_i==empty_char)
	{
	  i++;
	  continue;
	}
      else if(line_i==equal_sign_char)
	{
	  constant_name=ab;
	  ab=empty_str;
	}
      else if(line_i==delimiter_char)
	{
	  constant_value=ab;
	}
      else
	{
	  line_i_str=line[i];
	  ab=ab+line_i_str;
	}
      i++;
    }
  values1.constant_name=constant_name;
  values1.constant_value=constant_value;
  return values1;
}
