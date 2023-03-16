/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "rk4.h"
#include "../class/Solutions.h"
#include "../global/global.h"
#include "../eqs/parse_compartment_eqs_for_num_calc.h"
#include "../debug/debug.h"

Solutions for_calculation;
vector<Solution> data1;

void numerical_calculation_begin()
{
  int i=0;
  const int size=final_equations_for_calculation.size();
  string compartment_name;
  Equations equations_adding_to_compartment;
  Equations equations_subtracting_from_compartment;
  CompartmentEquationsAddSubtract final_equations_for_calculation_i;

  while(i<=size-1)
    {
      final_equations_for_calculation_i=final_equations_for_calculation[i];
      compartment_name=final_equations_for_calculation_i.compartment;

      if(compartment_name!=VOID and compartment_name!=ORIGIN)
	{
	  equations_adding_to_compartment=final_equations_for_calculation_i.equations_add;
	  equations_subtracting_from_compartment=final_equations_for_calculation_i.equations_subtract;

	  data1=solution_prepare(compartment_name, equations_adding_to_compartment, equations_subtracting_from_compartment);
	  for_calculation.push_back(data1);
	}
      i++;
    }
  final_equations_for_calculation.clear();
}
