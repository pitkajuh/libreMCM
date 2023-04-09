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

#include <iostream>
using std::cout;

const string get_constant_value(string constant, const string iv_specific)
{
  const bool iv_empty=iv_specific.empty();

  if(iv_empty)
    {
      throw std::domain_error("Value for constant "+constant+" was not found.");
    }

  const int size=constant.size()-1;
  bool is_negative=false;
  string sign;
  string value;
  sign=constant[0];

  // Check if trying to get a negative value of a constant.
  if(sign==SUBTRACT)
    {
      constant=constant.substr(1, size);
      is_negative=true;
    }

  const ConstantsMapData data=constants_map[constant];
  map<string, string> specific_value=data.specific_value;
  value=specific_value[iv_specific];
  const bool is_empty=value.empty();

  if(is_empty)
    {
      value=data.unspecific_value;
    }

  if(is_negative)
    {
      value=SUBTRACT+value;
    }

  return value;
}
