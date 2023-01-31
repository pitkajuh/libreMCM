/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <string>
#include <vector>
#include <tuple>
#include "../rcompartment/read_compartment_definition.h"

using namespace std;

tuple<vector<vector<string>>, vector<vector<int>>, vector<vector<int>>, vector<vector<string>>> equations_sort(vector<vector<string>> equations, vector<vector<int>> numerical_calculation_order_of_operations, vector<vector<int>> indice_values, vector<vector<string>> param_data)
{
  int i=0;
  int j=0;
  int i_compartment_element=0;
  int i_compartment=0;
  int compartment_elements_total;
  vector<vector<tuple<string, string, int>>> parameter_data_all;
  vector<int> nr_of_elements;
  vector<vector<string>> equations_sorted;
  vector<vector<string>> param_data_sorted;
  vector<vector<int>> calc_order_sorted;
  vector<vector<int>> indice_values_sorted;

  tuple<vector<vector<string>>, vector<vector<int>>, vector<vector<int>>, vector<vector<string>>> result;

  tuple<string, // compartment_name
	     vector<
	       vector<
		 tuple<
		   string, // parameter name
		   string, // parameter value
		   int // parameter half-life, is zero if parameter is not a radionuclide
		   >>
	       >
	     >
        compartment_parameters_i;

  int parameter_data_all_size;

  while(i<=compartment_parameters.size()-1)
    {
      compartment_parameters_i=compartment_parameters[i];
      parameter_data_all=get<1>(compartment_parameters_i);
      parameter_data_all_size=parameter_data_all.size();
      nr_of_elements.push_back(parameter_data_all_size);
      i++;
    }

  // compartment_parameters.clear();

  vector<string> equation;
  vector<string> equation2;
  vector<int> order;
  vector<int> order2;
  vector<int> indice;
  vector<int> indice2;
  vector<string> param;
  vector<string> param2;

  while(j<=equations.size()/2-1)
    {
      if(j==0)
	{
	  compartment_elements_total=nr_of_elements[i_compartment];
	  i_compartment_element+=1;
	}

      equation=equations[j];
      equation2=equations[j+compartment_elements_total];

      equations_sorted.push_back(equation);
      equations_sorted.push_back(equation2);

      order=numerical_calculation_order_of_operations[j];
      order2=numerical_calculation_order_of_operations[j+compartment_elements_total];

      calc_order_sorted.push_back(order);
      calc_order_sorted.push_back(order2);

      indice=indice_values[j];
      indice2=indice_values[j+compartment_elements_total];

      indice_values_sorted.push_back(indice);
      indice_values_sorted.push_back(indice2);

      param=param_data[j];
      param2=param_data[j+compartment_elements_total];

      param_data_sorted.push_back(param);
      param_data_sorted.push_back(param2);

      j++;
    }

  result=make_tuple(equations_sorted, calc_order_sorted, indice_values_sorted, param_data_sorted);
  return result;
}
