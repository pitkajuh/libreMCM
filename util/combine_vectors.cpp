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
#include <string>

using std::string;
using std::vector;

vector<string> combine_vectors_sub(vector<string> vec_from, vector<string> vec_to, int from)
{
  int i=from;
  string fchar;

  while(i<=vec_from.size()-1)
    {
      fchar=vec_from[i];
      vec_to.push_back(fchar);
      i++;
    }
  return vec_to;
}

vector<string> combine_vectors(vector<string> vec1, int vec1_from, int vec1_to, vector<string> vec2)
{
  int i=0;
  vector<string> result;
  string fchar;

  while(i<=vec1.size()-1)
    {
      fchar=vec1[i];

      if(i==vec1_from)
	{
	  result=combine_vectors_sub(vec1, vec2, vec1_from);
	  i=vec1_to;
	}
      else
	{
	  result.push_back(fchar);
	}
      i++;
    }
  return result;
}

vector<string> combine_vectors2(vector<string> vec_from, vector<string> vec2_to)
{
  int i=0;
  string fchar;

  while(i<=vec_from.size()-1)
    {
      fchar=vec_from[i];
      vec2_to.push_back(fchar);
      i++;
    }
  return vec2_to;
}
