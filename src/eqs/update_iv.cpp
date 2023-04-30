/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../class/IndiceOperatorData.h"

const string update_iv(string iv, const vector<IndiceOperatorData> data, const int index)
{
  const int size=data.size()-1;

  if(size>=0)
    {
      int i=0;
      int index_i;
      IndiceOperatorData data_i;

      while(i<=size)
	{
	  data_i=data[i];
	  index_i=data_i.index;

	  if(index==index_i)
	    {
	      data_i.index_value=iv;
	      iv=data_i.get_result();
	      break;
	    }
	  i++;
	}
    }
  return iv;
}
