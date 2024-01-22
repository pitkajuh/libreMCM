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
#include "../global/constants_map.h"
#include "../global/global_constants.h"
#include "../global/compartment_diagonal.h"
#include "../global/equation_constants.h"
#include "../util/is_in_vector.h"
#include "../util/valid_value_check.h"
#include "../util/s2d.h"
#include "../util/string_split.h"

using std::to_string;

void read_constants(const string line, const unordered_map<string, string> specific_values)
{
  const SplittedString splitted=string_split(line, EQUAL_SIGN);
  const string constant_name=splitted.splitted_string_part1;
  string constant_value=splitted.splitted_string_part2;
  value_check(constant_value);
  equation_constants.push_back(constant_name);
  const bool is_constant_compartment=is_in_vector(compartment_diagonal, constant_name);

  if(is_constant_compartment){throw std::domain_error("Constant "+constant_name+" cannot be defined. "+constant_name+" is already defined as a compartment.");}

  // Constant values might be given in scientific form. Converting the values from string to double and back to string will change them to decimal form.
  const double constant_value_num=s2d(constant_value);
  constant_value=to_string(constant_value_num);
  ConstantsMapData constant_data;
  constant_data.default_value=constant_value;
  constant_data.specific_value=specific_values;
  constants_map[constant_name]=constant_data;
}
