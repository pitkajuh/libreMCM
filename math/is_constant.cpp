/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../global/global_constants.h"
#include "../global/constants_map.h"

const bool is_constant(string fchar)
{
  bool result=false;
  const int size=fchar.size();
  string neg;

  neg=fchar[0];

  // Check if trying to get a negative value of a constant.
  if(neg==SUBTRACT)
    {
      fchar=fchar.substr(1, size);
    }

  const ConstantsMapData data=constants_map[fchar];
  const string value=data.unspecific_value;
  const bool is_empty=value.empty();

  if(!is_empty)
    {
      result=true;
    }

  return result;
}