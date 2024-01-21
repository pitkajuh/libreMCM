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
  int index_i;
  IndiceOperatorData data_i;

  for(const auto&i: data)
    {
      index_i=i.index;

      if(index==index_i)
	{
	  data_i.index_value=iv;
	  iv=data_i.get_result();
	  break;
	}
    }
  return iv;
}
