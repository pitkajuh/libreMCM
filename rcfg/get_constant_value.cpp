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
#include "read_bin.h"
#include "../global/global.h"

using std::to_string;

string get_constant_value(string constant)
{
  int i=0;
  int size=constants.size();
  int constant_size=constant.size();
  bool value_found=false;
  bool constant_negative=false;
  string value;
  string compare;
  double value_double;
  ConstantNameAndValue constants_i;

  if(constant_size==2)
    {
      // Check if the value is negative.
      constant=constant[1];
      constant_negative=true;
    }

  while(i<=size-1)
    {
      constants_i=constants[i];
      compare=constants_i.constant_name;

      if(constant==compare)
	{
	  value_found=true;
	  value=constants_i.constant_value;
	  value_double=stod(value);
	  value=to_string(value_double);

	  if(constant_negative)
	    {
	      // Value is negative, adding minus sign.
	      value=SUBTRACT+value;
	    }
	  break;
	}
      i++;
    }

  if(value_found)
    {
      return value;
    }
  else
    {
      throw std::domain_error("Constant value "+constant+" was not found.");
      return NULL;
    }
}
