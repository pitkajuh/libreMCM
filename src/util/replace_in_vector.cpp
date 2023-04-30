/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../class/VectorReplaceFromTo.h"
#include "../global/global_constants.h"

const VectorReplaceFromTo update_indices(int from, int to, const vector<string> fa)
{
  const int size=fa.size();
  VectorReplaceFromTo result;

  if(from>0 and to<size-1)
    {
      const int from_updated=from-1;
      const int to_updated=to+1;
      const string fa_im1=fa[from_updated];
      const string fa_ip1=fa[to_updated];

      if(to-from==2 and fa_im1==OPEN_PARENTHESIS and fa_ip1==CLOSE_PARENTHESIS)
	{
	  from=from_updated;
	  to=to_updated;
	}
    }
  result.index_from=from;
  result.index_to=to;
  return result;
}

vector<string> replace_in_vector2(vector<string> fa, const string result, int from, int to)
{
  if(from==to)
    {
      fa[from]=result;
    }
  else
    {
      fa[to]=result;
      fa.erase(fa.begin()+from, fa.begin()+to);
    }
  return fa;
}

vector<string> replace_in_vector(vector<string> fa, const string result, int from, int to)
{
  const VectorReplaceFromTo updated_indices=update_indices(from, to, fa);

  from=updated_indices.index_from;
  to=updated_indices.index_to;

  if(from==to)
    {
      fa[from]=result;
    }
  else
    {
      fa[to]=result;
      fa.erase(fa.begin()+from, fa.begin()+to);
    }
  return fa;
}
