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
#include "parse_compartment_eqs_for_num_calc.h"
#include "rk4.h"

using namespace std;

vector<vector<tuple<string, tuple<vector<string>, vector<int>, vector<string>>, vector<int>, vector<string>, vector<string>>>> for_calculation;
vector<tuple<string, tuple<vector<string>, vector<int>, vector<string>>, vector<int>, vector<string>, vector<string>>> data1;

void numerical_calculation_begin()
{
  int i=0;
  string compartment_name;
  vector<vector<string>> equations_adding_to_compartment;
  vector<vector<string>> equations_subtracting_from_compartment;
  tuple<string, vector<vector<string>>, vector<vector<string>>> final_equations_for_calculation_i;

  while(i<=final_equations_for_calculation.size()-1)
    {
      final_equations_for_calculation_i=final_equations_for_calculation[i];
      compartment_name=get<0>(final_equations_for_calculation_i);
      equations_adding_to_compartment=get<1>(final_equations_for_calculation_i);
      equations_subtracting_from_compartment=get<2>(final_equations_for_calculation_i);
      data1=solution_prepare(compartment_name, equations_adding_to_compartment, equations_subtracting_from_compartment);
      for_calculation.push_back(data1);
      i++;
    }
}
