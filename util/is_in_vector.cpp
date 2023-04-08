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
#include <vector>

using std::string;
using std::vector;

const bool is_in_vector(const vector<string> vec, const string str_find)
{
  // Checks if a string is in a string of vectors and return true/false.
  const int size=vec.size();
  bool rt=false;

  if(size>0)
    {
      for(const auto&i: vec)
	{
	  if(str_find==i)
	    {
	      rt=true;
	      break;
	    }
	}
    }
  return rt;
}
