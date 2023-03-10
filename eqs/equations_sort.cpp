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

Data equations_sort(Equations equations, VecVecInt numerical_calculation_order_of_operations, VecVecInt indice_values, VecVecString param_data)
{
  int i=0;
  int j=0;
  int i_compartment_element=0;
  int i_compartment=0;
  int compartment_parameters_size=compartment_parameters.get_size();
  int compartment_elements_total;
  int parameter_data_all_size;
  vector<int> nr_of_elements;
  Equations equations_sorted;
  VecVecString param_data_sorted;
  VecVecInt calc_order_sorted;
  VecVecInt indice_values_sorted;
  CompartmentAllInitialValuesHalfLife compartment_parameters_i;
  AllInitialValuesHalfLife parameter_data_all;
  Data result;

  while(i<=compartment_parameters_size-1)
    {
      compartment_parameters_i=compartment_parameters.get(i);
      parameter_data_all=compartment_parameters_i.initial_values;
      parameter_data_all_size=parameter_data_all.get_size();
      nr_of_elements.push_back(parameter_data_all_size);
      i++;
    }

  vector<string> equation;
  vector<string> equation2;
  vector<int> order;
  vector<int> order2;
  vector<int> indice;
  vector<int> indice2;
  vector<string> param;
  vector<string> param2;
  int size=equations.get_size()/2;
  int j_p1;

  while(j<=size-1)
    {
      if(j==0)
	{
	  compartment_elements_total=nr_of_elements[i_compartment];
	  i_compartment_element+=1;
	}

      equation=equations.get(j);
      j_p1=j+compartment_elements_total;
      equation2=equations.get(j_p1);

      equations_sorted.push_back(equation);
      equations_sorted.push_back(equation2);

      order=numerical_calculation_order_of_operations.get(j);
      order2=numerical_calculation_order_of_operations.get(j_p1);

      calc_order_sorted.push_back(order);
      calc_order_sorted.push_back(order2);

      indice=indice_values.get(j);
      indice2=indice_values.get(j_p1);

      indice_values_sorted.push_back(indice);
      indice_values_sorted.push_back(indice2);

      param=param_data.get(j);
      param2=param_data.get(j_p1);

      param_data_sorted.push_back(param);
      param_data_sorted.push_back(param2);

      j++;
    }
  result.equations_sorted=equations_sorted;
  result.calc_order_sorted=calc_order_sorted;
  result.indice_values_sorted=indice_values_sorted;
  result.param_data_sorted=param_data_sorted;
  return result;
}
