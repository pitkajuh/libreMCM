/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#ifndef INDICEOPERATORDATA_H
#define INDICEOPERATORDATA_H

#include "IndiceOperator.h"
#include "../global/global_constants.h"
#include "../math/calculate_order_of_operations.h"

class IndiceOperatorData
{
public:
  IndiceOperator* operator_data;
  int index; // Index of the equation which the operator operates on.
  bool is_negative; // Index of the equation may have a negative coefficient, which must be applied after the operator has been calculated.
  string index_value;

  const string get_result()
  {
    string result=operator_data->get_result(index_value);

    if(is_negative)
      {
	string sign;
	sign=result[0];

	if(sign==SUBTRACT)
	  {
	    const int size1=result.size()-1;
	    result=result.substr(1, size1);
	  }
	else
	  {
	    result=SUBTRACT+result;
	  }
      }
    return result;
  }
};

#endif
