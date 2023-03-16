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

vector<string> combine_vectors(const vector<string> vec_from, vector<string> vec_to)
{
  const int size=vec_from.size();

  if(size>0)
    {
      for(const auto&i: vec_from)
	{
	  vec_to.push_back(i);
	}
    }
  return vec_to;
}
