/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <stdexcept>
#include "../global/global_constants.h"
#include "../global/constants_map.h"

const string get_constant_value(string constant, const string iv_specific)
{
  int size=constant.size()-1;
  string sign;
  sign=constant[0];

  bool is_negative;

  if(sign==SUBTRACT)
    {
      constant=constant.substr(1, size);
      is_negative=true;
    }

  const bool iv_empty=iv_specific.empty();

  if(iv_empty){throw std::domain_error("Value for constant "+constant+" was not found.");}

  const ConstantsMapData data=constants_map[constant];
  unordered_map<string, string> specific_value=data.specific_value;
  string value=specific_value[iv_specific];
  const bool is_empty=value.empty();

  if(is_empty){value=data.default_value;}

  if(is_negative)
    {
      sign=value[0];

      if(sign==SUBTRACT)
	{
	  size=value.size()-1;
	  value=value.substr(1, size);
	}
      else{value=SUBTRACT+value;}
    }
  return value;
}
