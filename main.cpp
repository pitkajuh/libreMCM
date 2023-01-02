/*--------------------------------*- C++ -*----------------------------------*\
|                               +===========+                                |
|                               | l         |                                |
|                               |   i       | M ulti                         |
|                               |     b     | C ompartment                   |
|                               |       r   | M odelling                     |
|                               |         e |                                |
|                               +===========+                                |
\*---------------------------------------------------------------------------*/

#include <iostream>
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
  cout<<"Start"<<endl;
  auto begin=std::chrono::high_resolution_clock::now();
  get_sim_params ();
  cout<<"SIm params ok"<<endl;
  parse_compartment_equations();
  cout<<"parse_compartment_equations(); ok"<<endl;
  parse_compartment_eqs_for_num_calc();
  cout<<"parse_compartment_eqs_for_num_calc ok"<<endl;
  numerical_calculation_begin();
  cout<<"numerical_calculation_begin ok"<<endl;
  calculate();
  runge_kutta();
  auto end=std::chrono::high_resolution_clock::now();
  auto duration=std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
  cout<<"Runtime: "<<duration.count()<<" milliseconds"<<endl;

  write_to_file();

  return 0;
}
