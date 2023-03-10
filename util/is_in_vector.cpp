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

IsInVector is_in_vector_compartment(vector<string> vec, string str_find)
{
  // Checks if a string is in a string of vectors and return true/false and indice.
  int i=0;
  int is_in_indice=-1;
  int size=vec.size();
  bool rt=false;
  string fchar;
  IsInVector result;

  if(size>0)
    {
      while(i<=size-1)
	{
	  fchar=vec[i];

	  if(str_find==fchar)
	    {
	      rt=true;
	      is_in_indice=i;
	      break;
	    }
	  i++;
	}
    }
  result.is_in_vector=rt;
  result.is_in_index=is_in_indice;
  return result;
}

IsInVector is_in_vector(vector<string> vec, string str_find)
{
  // Checks if a string is in a string of vectors and return true/false and indice.
  int i=0;
  int is_in_indice=-1;
  bool rt=false;
  string fchar;
  IsInVector result;

  if(vec.size()>0)
    {
      while(i<=vec.size()-1)
	{
	  fchar=vec[i];

	  if(str_find==fchar)
	    {
	      rt=true;
	      is_in_indice=i;
	      break;
	    }
	  i++;
	}
    }
  result.is_in_vector=rt;
  result.is_in_index=is_in_indice;
  return result;
}
