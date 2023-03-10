/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "parse_compartment_equations.h"
#include "../class/EquationsAll.h"
#include "../class/CompartmentEquationsAllParse.h"
#include "../rcompartment/get_compartment_equations.h"
#include "../debug/debug.h"

CompartmentEquationsAddSubtractAll final_equations_for_calculation;
CompartmentEquationsAllParse equations_for_calculation;
EquationsAll equations_add;
EquationsAll equations_subtract;
Equations equations_add_all;
Equations equations_subtract_all;
int int_add=0;
int int_subtract=0;

void push_to_all_equations(EquationsAll equations, bool add_or_not)
{
  int i=0;
  int j=0;
  int size=equations.get_size();
  int equations_size;
  Equations equations_i;
  vector<string> equations_i_j;

  while(i<=size-1)
    {
      equations_i=equations.get(i);
      equations_size=equations_i.get_size();

      while(j<=equations_size-1)
	{
	  equations_i_j=equations_i.get(j);

	  if(add_or_not)
	    {
	      equations_add_all.push_back(equations_i_j);
	    }
	  else
	    {
	      equations_subtract_all.push_back(equations_i_j);
	    }
	  j++;
	}
      j=0;
      i++;
    }
}

void get_equations_for_numerical_calculation()
{
  int i=0;
  int size=equations_for_calculation.get_size();
  int equations_add_size;
  int equations_subtract_size;
  string compartment_name;
  bool eq_add=true;
  bool eq_subtract=false;
  EquationsAll equations_add_1;
  EquationsAll equations_subtract_1;
  CompartmentEquationsAddSubtract final_equation_i;
  CompartmentEquationsAll equations_for_calculation_i;

  while(i<=size-1)
    {
      equations_for_calculation_i=equations_for_calculation.get(i);

      compartment_name=equations_for_calculation_i.compartment;
      equations_add_1=equations_for_calculation_i.equations_add;
      equations_subtract_1=equations_for_calculation_i.equations_subtract;

      equations_add_size=equations_add_1.get_size();
      equations_subtract_size=equations_subtract_1.get_size();

      if(equations_add_size>0 and equations_subtract_size>0)
	{
	  push_to_all_equations(equations_add_1, eq_add);
	  push_to_all_equations(equations_subtract_1, eq_subtract);

	  final_equation_i.compartment=compartment_name;
	  final_equation_i.equations_add=equations_add_all;
	  final_equation_i.equations_subtract=equations_subtract_all;

	  final_equations_for_calculation.push_back(final_equation_i);
	  equations_add_all.clear();
	  equations_subtract_all.clear();
	}
      else if(equations_add_size==0 and equations_subtract_size>0)
	{
	  push_to_all_equations(equations_subtract_1, eq_subtract);

	  final_equation_i.compartment=compartment_name;
	  final_equation_i.equations_add=equations_add_all;
	  final_equation_i.equations_subtract=equations_subtract_all;

	  final_equations_for_calculation.push_back(final_equation_i);
	  equations_add_all.clear();
	  equations_subtract_all.clear();
	}
      else if(equations_add_size>0 and equations_subtract_size==0)
	{
	  push_to_all_equations(equations_add_1, eq_add);

	  final_equation_i.compartment=compartment_name;
	  final_equation_i.equations_add=equations_add_all;
	  final_equation_i.equations_subtract=equations_subtract_all;

	  final_equations_for_calculation.push_back(final_equation_i);
	  equations_add_all.clear();
	}
      i++;
    }
  equations_for_calculation.clear();
}

void add_equations_for_numerical_calculation(string compartment_name)
{
  CompartmentEquationsAll equations_for_calculation_i1;
  equations_for_calculation_i1.compartment=compartment_name;
  equations_for_calculation_i1.equations_add=equations_add;
  equations_for_calculation_i1.equations_subtract=equations_subtract;
  equations_for_calculation.push_back(equations_for_calculation_i1);
  equations_add.clear();
  equations_subtract.clear();
}

void add_or_subtract_equations(Equations equations, bool add_equation)
{
  if(add_equation)
    {
      // Equations add material to system.
      equations_add.push_back(equations);
      int_add++;
    }
  else
    {
      // Equations subtract material from the system.
      equations_subtract.push_back(equations);
      int_subtract++;
    }
}

void parse_compartment_eqs_for_num_calc()
{
  int i=0;
  int size=rt_local_global.get_size();
  EquationsAddSubtract eqs;
  string compartment_name;
  string compartment_name_previous1;
  Equations equations;
  bool add_equation;
  bool add_equation_previous;
  bool last=false;
  bool first_comp=false;

  while(i<=size-1)
    {
      eqs=rt_local_global.get(i);
      compartment_name=eqs.compartment;

      if(!first_comp)
	{
	  compartment_name_previous1=compartment_name;
	  first_comp=true;
	}

      add_equation=eqs.add_equations;
      equations=eqs.equations;

      if(compartment_name_previous1!=compartment_name)
	{
	  add_equations_for_numerical_calculation(compartment_name_previous1);
	  int_add=0;
	  int_subtract=0;

	  if(i<size-1)
	    {
	      add_or_subtract_equations(equations, add_equation);
	    }
	}
      else
	{
	  add_or_subtract_equations(equations, add_equation);
	}
      compartment_name_previous1=compartment_name;
      i++;
    }
  add_equations_for_numerical_calculation(compartment_name_previous1);
  int_add=0;
  int_subtract=0;
  rt_local_global.clear();
}
