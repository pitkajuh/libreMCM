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
#include <tuple>
#include <algorithm>
#include "global.h"

using namespace std;

tuple<int, int> update_indices(int index_replace_from, int index_replace_to, vector<string> fa)
{
  string fa_im1;
  string fa_ip1;
  tuple<int, int> result;

  if(index_replace_from!=0 and index_replace_to!=fa.size()-1)
    {
      fa_im1=fa[index_replace_from-1];
      fa_ip1=fa[index_replace_to+1];

      if(index_replace_to-index_replace_from==2 and fa_im1==open_parenthesis and fa_ip1==close_parenthesis)
	{
	  index_replace_from=index_replace_from-1;
	  index_replace_to=index_replace_to+1;
	}
    }

  result=make_tuple(index_replace_from, index_replace_to);
  return result;
}

vector<string> replace_in_vector(vector<string> fa, string result, int index_replace_from, int index_replace_to)
{
  int i=0;
  vector<string> fa_edited;
  tuple<int, int> updated_indices=update_indices(index_replace_from, index_replace_to, fa);
  index_replace_from=get<0>(updated_indices);
  index_replace_to=get<1>(updated_indices);

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
