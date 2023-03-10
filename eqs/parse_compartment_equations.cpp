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
  int compartment_parameters_rt_size=compartment_parameters_rt.get_size();
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
      compartment_parameters_i=compartment_parameters_rt.get(i);
      compartment_parameters_i1=compartment_parameters_i.initial_values;
      compartment_parameters_i1_size=compartment_parameters_i1.get_size();

      while(j<=compartment_parameters_i1_size-1)
	{
	  compartment_parameters_i1_j=compartment_parameters_i1.get(j);
	  compartment_parameters_i1_j_size=compartment_parameters_i1_j.get_size();

	  while(k<=compartment_parameters_i1_j_size-1)
	    {
	      compartment_parameters_i1_j_k=compartment_parameters_i1_j.get(k);
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
  int i=0;
  int size=compartment_diagonal.size();
  string diagonal_element;
  string comptset;
  CompartmentEquationsAddSubtract compartment_equations;
  Equations eq1;
  Equations eq2;

  while(i<=size-1)
    {
      diagonal_element=compartment_diagonal[i];
      compartment_equations=get_equations_compartment(diagonal_element);

      comptset=compartment_equations.compartment;
      eq1=compartment_equations.equations_add;
      eq2=compartment_equations.equations_subtract;
      equations_with_compartment_name.push_back(compartment_equations);
      i++;
    }
  parse_compartment_equations_subsubroutine();
}

void calculate_equation_with(Equations equations, bool equation_add, string compartment_name, int compartment_start_index)
{
  const int index_value=0;
  int i=index_value;
  int j=index_value;
  int size=equations.get_size();
  int equation_size;
  vector<string> equation;
  EquationsAddSubtract result;

  if(size>0)
    {
      while(i<=size-1)
	{
	  equation=equations.get(i);
	  equation_size=equation.size();

	  if(equation_size>0)
	    {
	      result=replace_param_eq(equation, equation_add, compartment_name, compartment_start_index, index_value);
	      rt_local_global.push_back(result);
	    }
	  i++;
	}
    }
}

void parse_compartment_equations()
{
  int i=0;
  int size=equations_with_compartment_name.get_size();
  int size_equations_add;
  int size_equations_subtract;
  Equations equations_add;
  Equations equations_subtract;
  string compartment_name;
  CompartmentEquationsAddSubtract vector;
  bool adding=true;
  bool subtracting=false;

  while(i<=size-1)
    {
      vector=equations_with_compartment_name.get(i);
      compartment_name=vector.compartment;
      equations_add=vector.equations_add;
      equations_subtract=vector.equations_subtract;
      size_equations_add=equations_add.get_size();
      size_equations_subtract=equations_subtract.get_size();

      if(compartment_name!=void_element and compartment_name!=origin_element)
	{
	  if(size_equations_add>0)
	    {
	      calculate_equation_with(equations_add, adding, compartment_name, i);
	    }
	  if(size_equations_subtract>0)
	    {
	      calculate_equation_with(equations_subtract, subtracting, compartment_name, i);
	    }
	}
      i++;
    }
}
