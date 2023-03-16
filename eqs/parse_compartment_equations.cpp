/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "parse_equations_sub.h"
#include "../class/CompartmentEquationsAddSubtractAll.h"
#include "../class/EquationsAddSubtractAll.h"
#include "../class/AllCompartmentInitialValuesHalfLife.h"
#include "../class/CompartmentInitialValuesHalfLife.h"
#include "../class/CompartmentAllInitialValuesHalfLife.h"
#include "../global/global.h"
#include "../rcompartment/read_compartment.h"
#include "../rcompartment/read_compartment_definition.h"
#include "../rcompartment/get_compartment_equations.h"
#include "../wdata/values_to_graph.h"
#include "../debug/debug.h"

CompartmentEquationsAddSubtractAll equations_with_compartment_name;
AllCompartmentInitialValuesHalfLife all_values;
EquationsAddSubtractAll rt_local_global;

AllCompartmentInitialValuesHalfLife parse_compartment_equations_subsubroutine()
{
  int i=0;
  int j=0;
  int k=0;
  int compartment_parameters_i1_size;
  int compartment_parameters_i1_j_size;
  const int compartment_parameters_rt_size=compartment_parameters_rt.size();
  float half_life;
  string compartment_element_name;
  string compartment_element_value;
  string name;
  string compartment_i;
  CompartmentAllInitialValuesHalfLife compartment_parameters_i;
  AllInitialValuesHalfLife compartment_parameters_i1;
  InitialValuesHalfLife compartment_parameters_i1_j;
  InitialValueHalfLife compartment_parameters_i1_j_k;
  CompartmentAllInitialValuesHalfLife add_values_i;
  InitialValuesHalfLife values;
  vector<InitialValuesHalfLife> values_i;
  AllInitialValuesHalfLife values_ii;

  while(i<=compartment_parameters_rt_size-1)
    {
      compartment_parameters_i=compartment_parameters_rt[i];
      compartment_parameters_i1=compartment_parameters_i.initial_values;
      compartment_parameters_i1_size=compartment_parameters_i1.size();

      while(j<=compartment_parameters_i1_size-1)
	{
	  compartment_parameters_i1_j=compartment_parameters_i1[j];
	  compartment_parameters_i1_j_size=compartment_parameters_i1_j.size();

	  while(k<=compartment_parameters_i1_j_size-1)
	    {
	      compartment_parameters_i1_j_k=compartment_parameters_i1_j[k];
	      values.push_back(compartment_parameters_i1_j_k);
	      k++;
	    }
	  k=0;
	  j++;
	}
      name=compartment_parameters_i.compartment;
      add_values_i.compartment=name;
      values_i.push_back(values);
      values_ii.initial_values=values_i;
      add_values_i.initial_values=values_ii;
      all_values.push_back(add_values_i);
      values_i.clear();
      values.clear();
      j=0;
      i++;
    }
  add_all_values();
  return all_values;
}

void parse_compartment_equations_subroutine()
{
  string comptset;
  CompartmentEquationsAddSubtract compartment_equations;
  Equations eq1;
  Equations eq2;

  for(const auto&i: compartment_diagonal)
    {
      compartment_equations=get_equations_compartment(i);

      comptset=compartment_equations.compartment;
      eq1=compartment_equations.equations_add;
      eq2=compartment_equations.equations_subtract;

      equations_with_compartment_name.push_back(compartment_equations);
    }
  parse_compartment_equations_subsubroutine();
}

void calculate_equation_with(Equations equations, const bool equation_add, const string compartment_name)
{
  const int size=equations.size();
  const int index_value=0;
  int i=index_value;
  int equation_size;
  vector<string> equation;
  EquationsAddSubtract result;

  if(size>0)
    {
      while(i<=size-1)
	{
	  equation=equations[i];
	  equation_size=equation.size();

	  if(equation_size>0)
	    {
	      result=replace_param_eq(equation, equation_add, compartment_name);
	      rt_local_global.push_back(result);
	    }
	  i++;
	}
    }
}

void parse_compartment_equations()
{
  int i=0;
  const int size=equations_with_compartment_name.size();
  int size_equations_add;
  int size_equations_subtract;
  string compartment_name;
  const bool adding=true;
  const bool subtracting=false;
  Equations equations_add;
  Equations equations_subtract;
  CompartmentEquationsAddSubtract vector;

  while(i<=size-1)
    {
      vector=equations_with_compartment_name[i];
      compartment_name=vector.compartment;
      equations_add=vector.equations_add;
      equations_subtract=vector.equations_subtract;
      size_equations_add=equations_add.size();
      size_equations_subtract=equations_subtract.size();

      if(compartment_name!=VOID and compartment_name!=ORIGIN)
	{
	  if(size_equations_add>0)
	    {
	      calculate_equation_with(equations_add, adding, compartment_name);
	    }
	  if(size_equations_subtract>0)
	    {
	      calculate_equation_with(equations_subtract, subtracting, compartment_name);
	    }
	}
      i++;
    }
}
