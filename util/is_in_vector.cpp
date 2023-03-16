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
#include "../class/IsInVector.h"

using std::string;
using std::vector;

IsInVector is_in_vector(const vector<string> vec, const string str_find)
{
  // Checks if a string is in a string of vectors and return true/false and indice.
  int j=0;
  int is_in_indice=-1;
  const int size=vec.size();
  bool rt=false;
  IsInVector result;

  if(size>0)
    {
      for(const auto&i: vec)
	{
	  if(str_find==i)
	    {
	      rt=true;
	      is_in_indice=j;
	      break;
	    }
	  j++;
	}
    }

  result.is_in_vector=rt;
  result.is_in_index=is_in_indice;
  return result;
}
