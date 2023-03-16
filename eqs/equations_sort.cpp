/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include "../class/CompartmentAllInitialValuesHalfLife.h"
#include "../class/Data.h"
#include "../rcompartment/read_compartment_definition.h"

Data equations_sort(Equations equations, const VecVecInt numerical_calculation_order_of_operations, const VecVecInt indice_values, SplittedStrings param_data)
{
  int i=0;
  int j=0;
  int i_compartment=0;
  int compartment_elements_total=0;
  int parameter_data_all_size;
  const int compartment_parameters_size=compartment_parameters.size();
  vector<int> nr_of_elements;
  Equations equations_sorted;
  SplittedStrings param_data_sorted;
  VecVecInt calc_order_sorted;
  VecVecInt indice_values_sorted;
  CompartmentAllInitialValuesHalfLife compartment_parameters_i;
  AllInitialValuesHalfLife parameter_data_all;
  Data result;
  const int size1=equations.size();
  const int divisible_by=2;

  if(size1>1 and size1 % divisible_by==0)
    {
      while(i<=compartment_parameters_size-1)
	{
	  compartment_parameters_i=compartment_parameters[i];
	  parameter_data_all=compartment_parameters_i.initial_values;
	  parameter_data_all_size=parameter_data_all.size();
	  nr_of_elements.push_back(parameter_data_all_size);
	  i++;
	}
      vector<string> equation;
      vector<string> equation2;
      vector<int> order;
      vector<int> order2;
      vector<int> indice;
      vector<int> indice2;
      vector<SplittedString> param;
      vector<SplittedString> param2;
      int j_p1;
      const int size=equations.size()/2;

      if(j==0)
	{
	  compartment_elements_total=nr_of_elements[i_compartment];
	  j_p1=j+compartment_elements_total;
	}

      while(j<=size-1)
	{
	  equation=equations[j];
	  j_p1=j+compartment_elements_total;
	  equation2=equations[j_p1];
	  equations_sorted.push_back(equation);
	  equations_sorted.push_back(equation2);

	  order=numerical_calculation_order_of_operations[j];
	  order2=numerical_calculation_order_of_operations[j_p1];

	  calc_order_sorted.push_back(order);
	  calc_order_sorted.push_back(order2);

	  indice=indice_values[j];
	  indice2=indice_values[j_p1];

	  indice_values_sorted.push_back(indice);
	  indice_values_sorted.push_back(indice2);

	  param=param_data[j];
	  param2=param_data[j_p1];

	  param_data_sorted.push_back(param);
	  param_data_sorted.push_back(param2);

	  j++;
	}
      result.equations_sorted=equations_sorted;
      result.calc_order_sorted=calc_order_sorted;
      result.indice_values_sorted=indice_values_sorted;
      result.param_data_sorted=param_data_sorted;
    }
  else
    {
      result.equations_sorted=equations;
      result.calc_order_sorted=numerical_calculation_order_of_operations;
      result.indice_values_sorted=indice_values;
      result.param_data_sorted=param_data;
    }
  return result;
}
