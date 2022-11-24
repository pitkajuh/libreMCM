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
#include <vector>
#include <algorithm>
#include "global.h"

using namespace std;

vector<string> replace_in_vector(vector<string> fa, string result, int index_replace_from, int index_replace_to)
{
  int i=0;
  vector<string> fa_edited, test;
  string fchar, empty, empty2;

  if(index_replace_to-index_replace_from==2 and fa[index_replace_from-1]==open_parenthesis and fa[index_replace_to+1]==close_parenthesis)
    {
      index_replace_from=index_replace_from-1;
      index_replace_to=index_replace_to+1;
    }

  if(index_replace_from==index_replace_to)
    {
      fa[index_replace_from]=result;
      fa_edited=fa;
    }
  else
    {
      i=index_replace_from;
      fa[index_replace_to]=result;

      while(i<index_replace_to)
	{
	  fa.erase(fa.begin()+i);
	  index_replace_to--;
	}

      fa_edited=fa;
    }

  return fa_edited;
}
