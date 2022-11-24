/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <chrono>
#include "read_sim_params.h"
#include "parse_compartment_equations.h"
#include "parse_compartment_eqs_for_num_calc.h"
#include "numerical_calculation_begin.h"
#include "numerical_calculation.h"
#include "write_to_file.h"

using namespace std;

int main()
{
  auto begin2 = std::chrono::high_resolution_clock::now();

  get_sim_params ();
  parse_compartment_equations();
  parse_compartment_eqs_for_num_calc();
  numerical_calculation_begin();
  calculate();
  write_to_file();

  auto end2 = std::chrono::high_resolution_clock::now();
  auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - begin2);

  cout<<"Runtime: "<<duration2.count()<<" milliseconds"<<endl;

  return 0;
}
