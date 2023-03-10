/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <vector>
#include <algorithm>
#include "../class/VectorReplaceFromTo.h"
#include "../global/global.h"

using std::vector;

VectorReplaceFromTo update_indices(int index_replace_from, int index_replace_to, vector<string> fa)
{
  VectorReplaceFromTo result;

  if(index_replace_from>0 and index_replace_to<fa.size()-1)
    {
      int from_updated=index_replace_from-1;
      int to_updated=index_replace_to+1;
      string fa_im1=fa[from_updated];
      string fa_ip1=fa[to_updated];

      if(index_replace_to-index_replace_from==2 and fa_im1==open_parenthesis and fa_ip1==close_parenthesis)
	{
	  index_replace_from=from_updated;
	  index_replace_to=to_updated;
	}
    }
  result.index_from=index_replace_from;
  result.index_to=index_replace_to;
  return result;
}

vector<string> replace_in_vector(vector<string> fa, string result, int index_replace_from, int index_replace_to)
{
  int i=0;
  vector<string> fa_edited;
  VectorReplaceFromTo updated_indices=update_indices(index_replace_from, index_replace_to, fa);

  index_replace_from=updated_indices.index_from;
  index_replace_to=updated_indices.index_to;

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

vector<string> replace_in_vector2(vector<string> fa, string result, int index_replace_from, int index_replace_to)
{
  int i=0;
  vector<string> fa_edited;

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
