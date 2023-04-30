/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "numerical_calculation_rules.h"
#include "../global/total_equation_indices.h"
#include "../global/compartment_indice_data.h"
#include "../global/compartment_total_equations.h"
#include "../global/global_constants.h"
#include "../math/calculate_equation_constants.h"
#include "../math/is_variable.h"
#include "../math/is_constant.h"

vector<string> replace_variable(vector<string> equation, const string dummy)
{
  int i=0;
  const int size=equation.size()-1;
  bool variable_check;
  string fchar;

  while(i<=size)
    {
      fchar=equation[i];
      variable_check=is_variable(fchar);

      if(variable_check)
	{
	  equation[i]=dummy;
	}
      i++;
    }
  return equation;
}

vector<string> replace_constant(vector<string> equation, const string dummy)
{
  int i=0;
  const int size=equation.size()-1;
  bool constant_check;
  string fchar;

  while(i<=size)
    {
      fchar=equation[i];
      constant_check=is_constant(fchar);

      if(constant_check)
	{
	  equation[i]=dummy;
	}
      i++;
    }
  return equation;
}

void replace_indices()
{
  int i=0;
  const int size=compartment_indice_data.size()-1;
  const string dummy="7";
  const string dummy2="5";
  string compartment_name;
  vector<int> compartment_indices;
  vector<int> calculation_indices;
  vector<string> total_equation;
  vector<string> compartment_names;
  IndicesData indices_data;
  CompartmentTotalEquation equation_data;

  while(i<=size)
    {
      indices_data=compartment_indice_data[i];
      compartment_names=indices_data.names;
      compartment_indices=indices_data.indices;

      equation_data=compartment_total_equations[i];
      total_equation=equation_data.total_equation;
      total_equation=replace_constant(total_equation, dummy2);
      total_equation=calculate_equation_constants(total_equation);
      total_equation=replace_variable(total_equation, dummy);
      calculation_indices=numerical_calculation_rules(total_equation);
      total_equation_indices.push_back(calculation_indices);
      i++;
    }
}
